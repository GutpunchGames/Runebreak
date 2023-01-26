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
	void AddPlayer1Input(FInput Input);
	void AddPlayer2Input(FInput Input);
	void AdvanceFrame();

	UFUNCTION(BlueprintCallable)
	int GetFrameCount();

private:
	UPROPERTY()
	ASimulationActor* Player1;

	UPROPERTY()
	ASimulationActor* Player2;

	UPROPERTY()
	int FrameCount = 0;

	// todo: ask why these need to be marked UPROPERTY
	UPROPERTY()
	UInputBuffer* Player1InputBuffer;
	UPROPERTY()
	UInputBuffer* Player2InputBuffer;

	ASimulationActor* SpawnPlayer(UClass* PlayerClass, FVector const& PlayerSpawnPoint);
	ASimulationActor* SpawnSimulationActor(UClass* Class, FVector const& Location);

	void SerializeState();
};
