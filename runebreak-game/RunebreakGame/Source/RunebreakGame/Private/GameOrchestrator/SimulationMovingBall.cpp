// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SimulationMovingBall.h"

void ASimulationMovingBall::SimulationTick(UInputBuffer* InputBuffer) {
	FVector NewLocation = GetActorLocation();
	FInput Input = InputBuffer->GetMostRecentInput();
	NewLocation.Z += Input.Direction;
	SetActorLocation(NewLocation);
}

FString ASimulationMovingBall::SerializeState() {
	return "";
}
