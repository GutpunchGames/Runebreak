// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SimulationMovingBall.h"

void ASimulationMovingBall::SimulationTick(UInputBuffer* InputBuffer) {
	if (InputBuffer->MoveDirection != 0) {
		FVector NewLocation = GetActorLocation();
		NewLocation.Z += InputBuffer->MoveDirection;
		SetActorLocation(NewLocation);
		UE_LOG(LogTemp, Warning, TEXT("New location: %s"), *NewLocation.ToString())
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No movement"))
	}
}

FString ASimulationMovingBall::SerializeState() {
	return "";
}
