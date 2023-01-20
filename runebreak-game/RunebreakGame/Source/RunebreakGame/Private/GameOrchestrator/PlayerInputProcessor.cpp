// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/PlayerInputProcessor.h"

UPlayerInputProcessor::UPlayerInputProcessor() {
	MoveDirection = 0;
}

void UPlayerInputProcessor::Bind(UInputComponent* InputComponent) {
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Bind"))
		InputComponent->BindAction("MoveUp", IE_Pressed, this, &UPlayerInputProcessor::HandleMoveUpPressed);
		InputComponent->BindAction("MoveUp", IE_Released, this, &UPlayerInputProcessor::HandleMoveUpReleased);
		InputComponent->BindAction("MoveDown", IE_Pressed, this, &UPlayerInputProcessor::HandleMoveDownPressed);
		InputComponent->BindAction("MoveDown", IE_Released, this, &UPlayerInputProcessor::HandleMoveDownReleased);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Fail"))
	}
}

void UPlayerInputProcessor::HandleMoveUpPressed() {
	UE_LOG(LogTemp, Warning, TEXT("Move Up Pressed"))
	MoveDirection = 1;
}

void UPlayerInputProcessor::HandleMoveUpReleased() {
	UE_LOG(LogTemp, Warning, TEXT("Move Up Released"))
	if (MoveDirection == 1) {
		MoveDirection = 0;
	}
}

void UPlayerInputProcessor::HandleMoveDownPressed() {
	UE_LOG(LogTemp, Warning, TEXT("Move Down Pressed"))
	MoveDirection = -1;
}

void UPlayerInputProcessor::HandleMoveDownReleased() {
	UE_LOG(LogTemp, Warning, TEXT("Move Down Released"))
	if (MoveDirection == -1) {
		MoveDirection = 0;
	}
}
