// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameSimulation.h"
#include <RunebreakGame/Public/GameOrchestrator/SimulationMovingBall.h>
#include <RunebreakGame/Public/GameOrchestrator/InputBuffer/LocalInputBuffer.h>
#include <RunebreakGame/Public/GameOrchestrator/InputBuffer/RemoteInputBuffer.h>

void UGameSimulation::Initialize(
	UClass* PlayerClass,
	FVector Player1SpawnPoint,
	FVector Player2SpawnPoint,
	bool IsPlayer1Remote,
	bool IsPlayer2Remote,
	int InputDelay
) {
	if (IsPlayer1Remote && IsPlayer2Remote) {
		UE_LOG(LogTemp, Error, TEXT("two remote players is not supported"))
	}
	SavedStateManager = NewObject<USavedStateManager>(this, "SavedStateManager");
	FrameCount = 0;
	Player1InputBuffer = IsPlayer1Remote ? Cast<UObject>(NewObject<URemoteInputBuffer>(this, "Player1InputBuffer")): Cast<UObject>(NewObject<ULocalInputBuffer>(this, "Player1InputBuffer"));
	Player2InputBuffer = IsPlayer2Remote ? Cast<UObject>(NewObject<URemoteInputBuffer>(this, "Player2InputBuffer")): Cast<UObject>(NewObject<ULocalInputBuffer>(this, "Player2InputBuffer"));

	if (InputDelay > 0) {
		if (!IsPlayer1Remote) {
			Cast<ULocalInputBuffer>(Player1InputBuffer)->Delay = InputDelay;
			FString Msg = FString::Printf(TEXT("added delay for player 1: %d"), InputDelay);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, Msg);
		}
		if (!IsPlayer2Remote) {
			Cast<ULocalInputBuffer>(Player2InputBuffer)->Delay = InputDelay;
			FString Msg = FString::Printf(TEXT("added delay for player 2: %d"), InputDelay);
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, Msg);
		}
	}
	Player1 = SpawnPlayer(0, PlayerClass, Player1SpawnPoint);
	Player2 = SpawnPlayer(1, PlayerClass, Player2SpawnPoint);
}

void UGameSimulation::AddPlayer1Input(const FInput& Input) {
	Cast<ULocalInputBuffer>(Player1InputBuffer)->AddInput(Input);
}

void UGameSimulation::AddPlayer2Input(const FInput& Input) {
	Cast<ULocalInputBuffer>(Player2InputBuffer)->AddInput(Input);
}

void UGameSimulation::AdvanceFrame() {
	for (int i = 0; i < SimulationActors.Num(); i++) {
		SimulationActors[i]->SimulationTick(FrameCount, Cast<IInputBuffer>(Player1InputBuffer), Cast<IInputBuffer>(Player2InputBuffer));
	}
	FrameCount++;
}

void UGameSimulation::SaveSnapshot() {
	SavedStateManager->Save(FrameCount, SimulationActors);
}

void UGameSimulation::LoadSnapshot(int Frame) {
	// todo: do this
}

int UGameSimulation::GetFrameCount() {
	return FrameCount;
}

void UGameSimulation::HandleSync(int Player, const FSyncMessage& SyncMessage) {
	UObject* InputBuffer = Player == 1 ? Player1InputBuffer : Player2InputBuffer;
	Cast<URemoteInputBuffer>(InputBuffer)->AddRemoteInputs(SyncMessage.RecentInputs);
}

ASimulationActor* UGameSimulation::SpawnPlayer(int PlayerIndex, UClass* PlayerClass, FVector const& PlayerSpawnPoint) {
	ASimulationActor* Player = SpawnSimulationActor(PlayerClass, PlayerSpawnPoint);
	Cast<ASimulationMovingBall>(Player)->PlayerIndex = PlayerIndex;
	return Player;
}

ASimulationActor* UGameSimulation::SpawnSimulationActor(UClass* Class, FVector const& Location) {
	FRotator Rotator = FRotator(0, 0, 0);
	ASimulationActor* SimulationActor = (ASimulationActor*)GetWorld()->SpawnActor(Class, &Location, &Rotator);
	SimulationActor->ActorId = ActorIdCounter;
	ActorIdCounter++;
	SimulationActors.Emplace(SimulationActor);
	return SimulationActor;
}

void UGameSimulation::DestroySimulationActor(int ActorId) {
	for (int i = 0; i < SimulationActors.Num(); i++) {
		ASimulationActor* SimulationActor = SimulationActors[i];
		SimulationActor->Destroy();
		SimulationActors.RemoveAt(i); // todo: use a map, this is bad
	}
}

void UGameSimulation::DestroyAllActors() {
	for (int i = 0; i < SimulationActors.Num(); i++) {
		ASimulationActor* SimulationActor = SimulationActors[i];
		SimulationActor->Destroy();
	}

	SimulationActors.Empty();
}
