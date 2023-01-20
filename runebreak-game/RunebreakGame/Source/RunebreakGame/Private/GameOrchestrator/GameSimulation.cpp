// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameSimulation.h"
#include <RunebreakGame/Public/GameOrchestrator/SimulationMovingBall.h>


void UGameSimulation::Initialize(UClass* PlayerClass, FVector PlayerSpawnPoint, int InputDelay) {
	InputBuffer = NewObject<UInputBuffer>(this, "InputBuffer1");
	InputBuffer->Delay = InputDelay;
	SpawnPlayer(PlayerClass, PlayerSpawnPoint);
}

void UGameSimulation::AddLocalInput(int MoveDirection) {
	FInput Input;
	Input.Direction = MoveDirection;
	InputBuffer->AddInput(Input);
}

void UGameSimulation::AdvanceFrame() {
	FrameCount++;
	Player->SimulationTick(InputBuffer);
}

void UGameSimulation::SerializeState() {

}

int UGameSimulation::GetFrameCount() {
	return FrameCount;
}

void UGameSimulation::SpawnPlayer(UClass* PlayerClass, FVector const& PlayerSpawnPoint) {
	Player = SpawnSimulationActor(PlayerClass, PlayerSpawnPoint);
}

ASimulationActor* UGameSimulation::SpawnSimulationActor(UClass* Class, FVector const& Location) {
	FRotator Rotator = FRotator(0, 0, 0);
	ASimulationActor* SimulationActor = (ASimulationActor*)GetWorld()->SpawnActor(Class, &Location, &Rotator);
	return SimulationActor;
}
