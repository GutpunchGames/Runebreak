// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator.h"

AGameOrchestrator::AGameOrchestrator() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AGameOrchestrator::BeginPlay() {
	Super::BeginPlay();

	if (InputComponent) {
		InputComponent->BindAction(
			"MoveUp",
			IE_Pressed,
			this,
			&AGameOrchestrator::HandleMoveUp
		);
		UE_LOG(LogTemp, Warning, TEXT("Bound HandleMoveUp"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Input Component"))
	}
}

void AGameOrchestrator::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void AGameOrchestrator::HandleMoveUp() {
	UE_LOG(LogTemp, Warning, TEXT("Handle Move Up"))
}
