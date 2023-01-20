// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator.h"

AGameOrchestrator::AGameOrchestrator() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AGameOrchestrator::BeginPlay() {
	Super::BeginPlay();
	PlayerInputProcessor = NewObject<UPlayerInputProcessor>(this, "GameOrchestratorPlayerInputProcessor");
	GameSimulation = NewObject<UGameSimulation>(this, "GameOrchestratorGameSimulation");
	BindInputs();

	GameSimulation->Initialize(PlayerClass, PlayerSpawnPoint, InputDelay);
}

void AGameOrchestrator::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	int MoveDirection = PlayerInputProcessor->MoveDirection;
	GameSimulation->AddLocalInput(MoveDirection);
	GameSimulation->AdvanceFrame();
}

void AGameOrchestrator::BindInputs() {
	PlayerInputProcessor->Bind(InputComponent);
}

