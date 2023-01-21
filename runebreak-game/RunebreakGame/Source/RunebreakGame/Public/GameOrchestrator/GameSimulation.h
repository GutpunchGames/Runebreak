// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include <RunebreakGame/Public/GameOrchestrator/InputBuffer.h>
#include <RunebreakGame/Public/GameOrchestrator/SimulationActor.h>
#include "GameSimulation.generated.h"

UCLASS()
class RUNEBREAKGAME_API UGameSimulation : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UClass* PlayerClass, FVector Player1SpawnPoint, FVector Player2SpawnPoint, int InputDelay);
	void AddPlayer1Input(FInput Inputj);
	void AddPlayer2Input(FInput Inputj);
	void AdvanceFrame();
	int GetFrameCount();

private:
	ASimulationActor* Player1;
	ASimulationActor* Player2;

	int FrameCount = 0;

	UInputBuffer* Player1InputBuffer;
	UInputBuffer* Player2InputBuffer;

	ASimulationActor* SpawnPlayer(UClass* PlayerClass, FVector const& PlayerSpawnPoint);
	ASimulationActor* SpawnSimulationActor(UClass* Class, FVector const& Location);
	void SerializeState();
};
