// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator.h"

AGameOrchestrator::AGameOrchestrator() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

void AGameOrchestrator::BeginPlay() {
	Super::BeginPlay();
	PlayerInputProcessor = NewObject<UPlayerInputProcessor>(this, "GameOrchestratorPlayerInputProcessor");
	BindInputs();
}

void AGameOrchestrator::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	int MoveDirection = PlayerInputProcessor->MoveDirection;
	if (MoveDirection == 1) {
		UE_LOG(LogTemp, Warning, TEXT("Moving Up"))
	}
	else if (MoveDirection == -1) {
		UE_LOG(LogTemp, Warning, TEXT("Moving Down"))
	}
	else if (MoveDirection == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Not Moving"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Moving weird direction: %d"), MoveDirection)
	}
}

void AGameOrchestrator::BindInputs() {
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Bind"))
		InputComponent->BindAction("MoveUp", IE_Pressed, this, &AGameOrchestrator::HandleMoveUpPressed);
		InputComponent->BindAction("MoveUp", IE_Released, this, &AGameOrchestrator::HandleMoveUpReleased);
		InputComponent->BindAction("MoveDown", IE_Pressed, this, &AGameOrchestrator::HandleMoveDownPressed);
		InputComponent->BindAction("MoveDown", IE_Released, this, &AGameOrchestrator::HandleMoveDownReleased);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Fail"))
	}
}

void AGameOrchestrator::HandleMoveUpPressed() {
	PlayerInputProcessor->HandleMoveUpPressed();
}

void AGameOrchestrator::HandleMoveUpReleased() {
	PlayerInputProcessor->HandleMoveUpReleased();
}

void AGameOrchestrator::HandleMoveDownPressed() {
	PlayerInputProcessor->HandleMoveDownPressed();
}

void AGameOrchestrator::HandleMoveDownReleased() {
	PlayerInputProcessor->HandleMoveDownReleased();
}
