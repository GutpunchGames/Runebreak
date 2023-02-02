// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SimulationMovingBall.h"
#include "Utilities/SerializationUtilities.h"

void ASimulationMovingBall::SimulationTick(int Frame, IInputBuffer* Player1InputBuffer, IInputBuffer* Player2InputBuffer) {
	FVector NewLocation = GetActorLocation();
	IInputBuffer* InputBuffer = PlayerIndex == 0 ? Player1InputBuffer : Player2InputBuffer;
	FInput Input = InputBuffer->GetInput(Frame);
	NewLocation.Z += Input.MoveDirection;
	SetActorLocation(NewLocation);
}

FString ASimulationMovingBall::SerializeState() {
	FVector Location = GetActorLocation();
	return SerializationUtilities::SerializeFVector(Location);
}


void ASimulationMovingBall::Deserialize(const FString& Bytes) {
	const FVector NewLocation = SerializationUtilities::DeserializeFVector(Bytes);
	SetActorLocation(NewLocation);
}