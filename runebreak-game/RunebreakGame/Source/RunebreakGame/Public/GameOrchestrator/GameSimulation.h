// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include <RunebreakGame/Public/GameOrchestrator/SimulationActor.h>
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/GameSocketMessages.h>
#include "GameSimulation.generated.h"

UCLASS()
class RUNEBREAKGAME_API UGameSimulation : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UClass* PlayerClass, FVector Player1SpawnPoint, FVector Player2SpawnPoint, bool IsPlayer1Remote, bool IsPlayer2Remote, int InputDelay);
	void AddPlayer1Input(const FInput& Input);
	void AddPlayer2Input(const FInput& Input);
	void AdvanceFrame();

	UFUNCTION(BlueprintCallable)
	int GetFrameCount();

	UFUNCTION()
	void HandleSync(int Player, const FSyncMessage& SyncMessage);

	// todo: make interface
	UPROPERTY()
	UObject* Player1InputBuffer;
	UPROPERTY()
	UObject* Player2InputBuffer;

private:
	UPROPERTY()
	ASimulationActor* Player1;

	UPROPERTY()
	ASimulationActor* Player2;

	UPROPERTY()
	int FrameCount = 0;

	ASimulationActor* SpawnPlayer(UClass* PlayerClass, FVector const& PlayerSpawnPoint);
	ASimulationActor* SpawnSimulationActor(UClass* Class, FVector const& Location);

	void SerializeState();
};
