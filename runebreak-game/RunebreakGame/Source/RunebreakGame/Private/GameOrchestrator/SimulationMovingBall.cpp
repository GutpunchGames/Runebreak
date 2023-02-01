// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SimulationMovingBall.h"

void ASimulationMovingBall::SimulationTick(int Frame, IInputBuffer* Player1InputBuffer, IInputBuffer* Player2InputBuffer) {
	FVector NewLocation = GetActorLocation();
	IInputBuffer* InputBuffer = PlayerIndex == 0 ? Player1InputBuffer : Player2InputBuffer;
	FInput Input = InputBuffer->GetInput(Frame);
	NewLocation.Z += Input.MoveDirection;
	SetActorLocation(NewLocation);
}

FString ASimulationMovingBall::SerializeState() {
	FVector Location = GetActorLocation();
	FString SerializedLocation = FString::Printf(TEXT("%d,%d,%d"), Location.X, Location.Y, Location.Z);
	return SerializedLocation;
}


void ASimulationMovingBall::Deserialize(const FString& Bytes) {
	FString X_STR;
	FString Y_STR;
	FString Z_STR;

	Bytes.Split(TEXT(","), &X_STR, &Y_STR, &Z_STR);

	FVector NewLocation;

	NewLocation.X = FCString::Atof(*X_STR);
	NewLocation.Y = FCString::Atof(*Y_STR);
	NewLocation.Z = FCString::Atof(*Z_STR);
	SetActorLocation(NewLocation);
}