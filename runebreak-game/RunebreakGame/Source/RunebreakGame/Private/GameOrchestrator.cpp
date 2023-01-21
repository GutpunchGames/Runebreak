// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator.h"

AGameOrchestrator::AGameOrchestrator() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AGameOrchestrator::BeginPlay() {
	Super::BeginPlay();
	Player1InputProcessor = NewObject<UPlayerInputProcessor>(this, "GameOrchestratorPlayer1InputProcessor");
	Player2InputProcessor = NewObject<UPlayerInputProcessor>(this, "GameOrchestratorPlayer2InputProcessor");
	GameSimulation = NewObject<UGameSimulation>(this, "GameOrchestratorGameSimulation");
	BindInputs();

	GameSimulation->Initialize(PlayerClass, Player1SpawnPoint->GetActorLocation(), Player2SpawnPoint->GetActorLocation(), InputDelay);
}

void AGameOrchestrator::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	GameSimulation->AddPlayer1Input(Player1InputProcessor->Input);
	GameSimulation->AddPlayer2Input(Player2InputProcessor->Input);
	GameSimulation->AdvanceFrame();
}

void AGameOrchestrator::BindInputs() {
	if (Player1SpawnPoint->PlayerSpawnConfig.ClientType == PlayerClientType::Local) {
		Player1InputProcessor->Bind(1, InputComponent);
	}
	if (Player2SpawnPoint->PlayerSpawnConfig.ClientType == PlayerClientType::Local) {
		Player2InputProcessor->Bind(2, InputComponent);
	}
}

