// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameSimulation.h"
#include <RunebreakGame/Public/GameOrchestrator/SimulationMovingBall.h>


void UGameSimulation::Initialize(
	UClass* PlayerClass,
	FVector Player1SpawnPoint,
	FVector Player2SpawnPoint,
	int InputDelay
) {
	Player1InputBuffer = NewObject<UInputBuffer>(this, "Player1InputBuffer");
	Player2InputBuffer = NewObject<UInputBuffer>(this, "Player2InputBuffer");
	Player1InputBuffer->Delay = InputDelay;
	Player1 = SpawnPlayer(PlayerClass, Player1SpawnPoint);
	Player2 = SpawnPlayer(PlayerClass, Player2SpawnPoint);
}

void UGameSimulation::AddPlayer1Input(FInput Input) {
	Player1InputBuffer->AddInput(Input);
}

void UGameSimulation::AddPlayer2Input(FInput Input) {
	Player2InputBuffer->AddInput(Input);
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

ASimulationActor* UGameSimulation::SpawnPlayer(UClass* PlayerClass, FVector const& PlayerSpawnPoint) {
	return SpawnSimulationActor(PlayerClass, PlayerSpawnPoint);
}

ASimulationActor* UGameSimulation::SpawnSimulationActor(UClass* Class, FVector const& Location) {
	FRotator Rotator = FRotator(0, 0, 0);
	ASimulationActor* SimulationActor = (ASimulationActor*)GetWorld()->SpawnActor(Class, &Location, &Rotator);
	return SimulationActor;
}
