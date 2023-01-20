// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include <RunebreakGame/Public/GameOrchestrator/SimulationActor.h>
#include "Math/Rotator.h"
#include "GameSimulation.generated.h"

UCLASS()
class RUNEBREAKGAME_API UGameSimulation : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UClass* PlayerClass, FVector PlayerSpawnPoint);
	void AddLocalInput(int MoveDirection);
	void AdvanceFrame();
	int GetFrameCount();


private:
	ASimulationActor* Player;
	int FrameCount = 0;

	int ThisFrameMoveDirection;
	void SpawnPlayer(UClass* PlayerClass, FVector const& PlayerSpawnPoint);
	ASimulationActor* SpawnSimulationActor(UClass* Class, FVector const& Location);
	void SerializeState();
};
