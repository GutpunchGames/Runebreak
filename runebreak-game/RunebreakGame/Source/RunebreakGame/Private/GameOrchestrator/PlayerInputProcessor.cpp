// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/PlayerInputProcessor.h"

UPlayerInputProcessor::UPlayerInputProcessor() {
	Input.MoveDirection = 0;
}

void UPlayerInputProcessor::Bind(int PlayerIndex, UInputComponent* InputComponent) {
	FString Prefix = FString::Printf(TEXT("Player%d"), PlayerIndex);
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Bind"))
		InputComponent->BindAction(FName(*(FString::Printf(TEXT("%sMoveUp"), *Prefix))), IE_Pressed, this, &UPlayerInputProcessor::HandleMoveUpPressed);
		InputComponent->BindAction(FName(*(FString::Printf(TEXT("%sMoveUp"), *Prefix))), IE_Released, this, &UPlayerInputProcessor::HandleMoveUpReleased);
		InputComponent->BindAction(FName(*(FString::Printf(TEXT("%sMoveDown"), *Prefix))), IE_Pressed, this, &UPlayerInputProcessor::HandleMoveDownPressed);
		InputComponent->BindAction(FName(*(FString::Printf(TEXT("%sMoveDown"), *Prefix))), IE_Released, this, &UPlayerInputProcessor::HandleMoveDownReleased);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Fail"))
	}
}

void UPlayerInputProcessor::SetRemoteInput(FInput _Input) {
	Input = _Input;
}

void UPlayerInputProcessor::HandleMoveUpPressed() {
	UE_LOG(LogTemp, Warning, TEXT("Move Up Pressed"))
	Input.MoveDirection = 1;
}

void UPlayerInputProcessor::HandleMoveUpReleased() {
	UE_LOG(LogTemp, Warning, TEXT("Move Up Released"))
	if (Input.MoveDirection == 1) {
		Input.MoveDirection = 0;
	}
}

void UPlayerInputProcessor::HandleMoveDownPressed() {
	UE_LOG(LogTemp, Warning, TEXT("Move Down Pressed"))
	Input.MoveDirection = -1;
}

void UPlayerInputProcessor::HandleMoveDownReleased() {
	UE_LOG(LogTemp, Warning, TEXT("Move Down Released"))
	if (Input.MoveDirection == -1) {
		Input.MoveDirection = 0;
	}
}
