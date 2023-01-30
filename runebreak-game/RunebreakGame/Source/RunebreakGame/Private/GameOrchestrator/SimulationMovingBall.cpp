// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SimulationMovingBall.h"

void ASimulationMovingBall::SimulationTick(int Frame, IInputBuffer* InputBuffer) {
	FVector NewLocation = GetActorLocation();
	FInput Input = InputBuffer->GetInput(Frame);
	UE_LOG(LogTemp, Warning, TEXT("Fetched input with frame: %d"), Frame)
	NewLocation.Z += Input.MoveDirection;
	SetActorLocation(NewLocation);
}

FString ASimulationMovingBall::SerializeState() {
	return "";
}
