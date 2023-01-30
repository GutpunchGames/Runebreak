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
	FrameCount = 0;
	Player1InputBuffer = IsPlayer1Remote ? Cast<UObject>(NewObject<URemoteInputBuffer>(this, "Player1InputBuffer")): Cast<UObject>(NewObject<ULocalInputBuffer>(this, "Player1InputBuffer"));
	Player2InputBuffer = IsPlayer2Remote ? Cast<UObject>(NewObject<URemoteInputBuffer>(this, "Player1InputBuffer")): Cast<UObject>(NewObject<ULocalInputBuffer>(this, "Player1InputBuffer"));

	if (InputDelay > 0) {
		if (!IsPlayer1Remote) {
			Cast<ULocalInputBuffer>(Player1InputBuffer)->Delay = InputDelay;
		}
		if (!IsPlayer2Remote) {
			Cast<ULocalInputBuffer>(Player2InputBuffer)->Delay = InputDelay;
		}
	}
	Player1 = SpawnPlayer(PlayerClass, Player1SpawnPoint);
	Player2 = SpawnPlayer(PlayerClass, Player2SpawnPoint);
}

void UGameSimulation::AddPlayer1Input(const FInput& Input) {
	Cast<ULocalInputBuffer>(Player1InputBuffer)->AddInput(Input);
}

void UGameSimulation::AddPlayer2Input(const FInput& Input) {
	Cast<ULocalInputBuffer>(Player2InputBuffer)->AddInput(Input);
}

void UGameSimulation::AdvanceFrame() {
	FrameCount++;
	Player1->SimulationTick(Player1InputBuffer);
	Player2->SimulationTick(Player2InputBuffer);
}

void UGameSimulation::SerializeState() {

}

int UGameSimulation::GetFrameCount() {
	return FrameCount;
}

void UGameSimulation::HandleSync(int Player, const FSyncMessage& SyncMessage) {
	UObject* InputBuffer = Player == 1 ? Player1InputBuffer : Player2InputBuffer;
	Cast<URemoteInputBuffer>(InputBuffer)->AddRemoteInputs(SyncMessage.RecentInputs);
}

ASimulationActor* UGameSimulation::SpawnPlayer(UClass* PlayerClass, FVector const& PlayerSpawnPoint) {
	return SpawnSimulationActor(PlayerClass, PlayerSpawnPoint);
}

ASimulationActor* UGameSimulation::SpawnSimulationActor(UClass* Class, FVector const& Location) {
	FRotator Rotator = FRotator(0, 0, 0);
	ASimulationActor* SimulationActor = (ASimulationActor*)GetWorld()->SpawnActor(Class, &Location, &Rotator);
	return SimulationActor;
}
