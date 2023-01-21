// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator.h"

AGameOrchestrator::AGameOrchestrator() {
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AGameOrchestrator::PrepareGame(int PlayerIndex) {
	Player1InputProcessor = NewObject<UPlayerInputProcessor>(this, "GameOrchestratorPlayer1InputProcessor");
	Player2InputProcessor = NewObject<UPlayerInputProcessor>(this, "GameOrchestratorPlayer2InputProcessor");
	BindInputs(PlayerIndex);

	GameSimulation = NewObject<UGameSimulation>(this, "GameOrchestratorGameSimulation");
	GameSimulation->Initialize(PlayerClass, Player1SpawnPoint->GetActorLocation(), Player2SpawnPoint->GetActorLocation(), InputDelay);

	PrimaryActorTick.SetTickFunctionEnable(true);
}

void AGameOrchestrator::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	GameSimulation->AddPlayer1Input(Player1InputProcessor->Input);
	GameSimulation->AddPlayer2Input(Player2InputProcessor->Input);
	GameSimulation->AdvanceFrame();
}

void AGameOrchestrator::BindInputs(int PlayerIndex) {
	if (PlayerIndex == 1) {
		Player1InputProcessor->Bind(1, InputComponent);
	}
	else if (PlayerIndex == 2) {
		Player2InputProcessor->Bind(2, InputComponent);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Invalid Player Index: %d"), PlayerIndex)
	}
}

