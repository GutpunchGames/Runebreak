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
	FString SerializedLocation = SerializationUtilities::SerializeFVector(Location);
	FString SerializedPlayerIndex = FString::Printf(TEXT("%d"), PlayerIndex);
	return SerializedPlayerIndex + SerializedLocation;
}

void ASimulationMovingBall::Deserialize(const FString& Bytes) {
	if (Bytes[0] == '1') {
		PlayerIndex = 1;
	}
	else if (Bytes[0] == '2') {
		PlayerIndex = 2;
	}

	const FVector NewLocation = SerializationUtilities::DeserializeFVector(&Bytes[1]);
	SetActorLocation(NewLocation);
}