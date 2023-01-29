// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameOrchestrator.h"

AGameOrchestrator::AGameOrchestrator() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	IsCorrectingRift = false;
}

void AGameOrchestrator::PrepareGame(FPlayerSpawnConfig Player1SpawnConfig, FPlayerSpawnConfig Player2SpawnConfig, int LocalPort) {
	Player1InputProcessor = NewObject<UPlayerInputProcessor>(this, "GameOrchestratorPlayer1InputProcessor");
	Player2InputProcessor = NewObject<UPlayerInputProcessor>(this, "GameOrchestratorPlayer2InputProcessor");

	IsPlayer1Remote = Player1SpawnConfig.ClientType == PlayerClientType::Remote;
	IsPlayer2Remote = Player2SpawnConfig.ClientType == PlayerClientType::Remote;
	IsAnyPlayerRemote = IsPlayer1Remote || IsPlayer2Remote;

	if (IsPlayer1Remote && IsPlayer2Remote) {
		UE_LOG(LogTemp, Error, TEXT("two remote players is not supported"))
			return;
	}

	if (!IsPlayer1Remote) {
		Player1InputProcessor->Bind(1, InputComponent);
	}
	if (!IsPlayer2Remote) {
		Player2InputProcessor->Bind(2, InputComponent);
	}

	FVector Player1SpawnLocation;
	Player1SpawnLocation.X = 0;
	Player1SpawnLocation.Y = -100;
	Player1SpawnLocation.Z = 0;

	FVector Player2SpawnLocation;
	Player2SpawnLocation.X = 0;
	Player2SpawnLocation.Y = 100;
	Player2SpawnLocation.Z = 0;
	GameSimulation = NewObject<UGameSimulation>(this, "GameOrchestratorGameSimulation");
	GameSimulation->Initialize(PlayerClass, Player1SpawnLocation, Player2SpawnLocation, InputDelay);

	if (IsPlayer1Remote) {
		FRBGameSocketConfig GameSocketConfig;
		GameSocketConfig.IsHost = false;
		GameSocketConfig.LogToScreen = LogSocketMessages;

		FUDPSocketConfig UDPSocketConfig;
		UDPSocketConfig.LocalPort = LocalPort;
		UDPSocketConfig.RemoteHost = Player1SpawnConfig.RemoteHost;
		UDPSocketConfig.RemotePort = Player1SpawnConfig.RemotePort;
		GameSocketConfig.UDPSocketConfig = UDPSocketConfig;

		GameSocket->SocketConfig = GameSocketConfig;
		GameSocket->Setup();
	} else if (IsPlayer2Remote) {
		FRBGameSocketConfig GameSocketConfig;
		GameSocketConfig.IsHost = true;
		GameSocketConfig.LogToScreen = LogSocketMessages;

		FUDPSocketConfig UDPSocketConfig;
		UDPSocketConfig.LocalPort = LocalPort;
		UDPSocketConfig.RemoteHost = Player2SpawnConfig.RemoteHost;
		UDPSocketConfig.RemotePort = Player2SpawnConfig.RemotePort;
		GameSocketConfig.UDPSocketConfig = UDPSocketConfig;

		GameSocket->SocketConfig = GameSocketConfig;
		GameSocket->Setup();
	}

	if (IsAnyPlayerRemote) {
		GameSocket->OnSyncReceivedDelegate.BindUObject(this, &AGameOrchestrator::HandleSyncMessage);
	}

	PrimaryActorTick.SetTickFunctionEnable(true);
}

// 60fps frame limited ticks
void AGameOrchestrator::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (!GameSimulation) {
		return;
	}

	int CurrentFrame = GameSimulation->GetFrameCount();
	if (IsAnyPlayerRemote) {
		GameSocket->SendPing(GameSimulation->GetFrameCount());
		GameSocket->ReceivePendingMessages();
	}

	bool ShouldAdvanceFrame = true;
	if (IsAnyPlayerRemote) {
		float Rift = IsAnyPlayerRemote ? ComputeRift() : 0;
		if (Rift >= RiftPauseThresholdFrames || IsCorrectingRift && Rift > 2) {
			ShouldAdvanceFrame = false;
			IsCorrectingRift = true;
		}
		else {
			IsCorrectingRift = false;
			ShouldAdvanceFrame = true;
		}
	}

	if (ShouldAdvanceFrame) {
		if (!IsPlayer1Remote && IsPlayer2Remote) {
			FInput PlayerInput = Player1InputProcessor->Input;
			PlayerInput.Frame = GameSimulation->GetFrameCount();
			GameSimulation->AddPlayer1Input(PlayerInput);

			FSyncMessage SyncMessage;

			int MostRecentRemoteAck = GameSocket->NetworkMonitor->NetworkStatistics.MostRecentRemoteAck;
			TArray<FInput> RecentInputs = GameSimulation->Player1InputBuffer->GetInputsSince(MostRecentRemoteAck);
			SyncMessage.RecentInputs = RecentInputs;

			SyncMessage.OriginFrame = GameSimulation->GetFrameCount();
			SyncMessage.FrameAck = GameSocket->NetworkMonitor->NetworkStatistics.MostRecentRemoteFrame;

			GameSocket->SendSync(SyncMessage);
		}
		else if (IsPlayer1Remote && !IsPlayer2Remote) {
			FInput PlayerInput = Player2InputProcessor->Input;
			PlayerInput.Frame = GameSimulation->GetFrameCount();
			GameSimulation->AddPlayer2Input(PlayerInput);

			FSyncMessage SyncMessage;

			int MostRecentRemoteAck = GameSocket->NetworkMonitor->NetworkStatistics.MostRecentRemoteAck;
			TArray<FInput> RecentInputs = GameSimulation->Player2InputBuffer->GetInputsSince(MostRecentRemoteAck);
			SyncMessage.RecentInputs = RecentInputs;

			SyncMessage.OriginFrame = GameSimulation->GetFrameCount();
			SyncMessage.FrameAck = GameSocket->NetworkMonitor->NetworkStatistics.MostRecentRemoteFrame;

			GameSocket->SendSync(SyncMessage);
		}
		else {
			FInput Player1Input = Player1InputProcessor->Input;
			Player1Input.Frame = GameSimulation->GetFrameCount();
			FInput Player2Input = Player2InputProcessor->Input;
			Player2Input.Frame = GameSimulation->GetFrameCount();

			GameSimulation->AddPlayer1Input(Player1Input);
			GameSimulation->AddPlayer2Input(Player2Input);
		}

		if (IsAnyPlayerRemote) {
			GameSocket->CurrentFrame = GameSocket->CurrentFrame + 1;
		}

		GameSimulation->AdvanceFrame();
		OnFrameAdvancedDelegate.ExecuteIfBound();
	}
}

void AGameOrchestrator::HandleSyncMessage(const FSyncMessage& SyncMessage) {
	if (!IsAnyPlayerRemote) {
		return;
	}

	if (IsPlayer1Remote) {
		GameSimulation->HandleSync(1, SyncMessage);
	}
	else {
		GameSimulation->HandleSync(2, SyncMessage);
	}
}

// computes the number of frames (with subframe precision) that two clients differ
// negative values imply that they are ahead of us, positive that we are ahead of them
// todo: consider network time
float AGameOrchestrator::ComputeRift() {

	FNetworkStatistics NetworkStatistics = GameSocket->NetworkMonitor->NetworkStatistics;
	int MostRecentRemoteFrame = NetworkStatistics.MostRecentRemoteFrame;
	//float AverageRoundTripTime = NetworkStatistics.AverageRoundTripTime;
	//float AverageOneWayTime = AverageRoundTripTime / (float)2;
	//float FrameTime = (float)1 / (float)60;
	//float AverageOneWayFrames = AverageOneWayTime / FrameTime;
	//float EstimatedCurrentRemoteFrame = (float) MostRecentRemoteFrame + AverageOneWayFrames;
	float EstimatedCurrentRemoteFrame = (float) MostRecentRemoteFrame;

	return (float) GameSimulation->GetFrameCount() - EstimatedCurrentRemoteFrame;
}

void AGameOrchestrator::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (GameSocket) {
		UE_LOG(LogTemp, Warning, TEXT("Tearing down socket"))
		GameSocket->Teardown();
	}
}


