// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <RunebreakGame/Public/GameOrchestrator/PlayerSpawnPoint.h>
#include <RunebreakGame/Public/GameOrchestrator/PlayerInputProcessor.h>
#include <RunebreakGame/Public/GameOrchestrator/GameSimulation.h>
#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include "GameOrchestrator.generated.h"

UCLASS(Blueprintable)
class RUNEBREAKGAME_API AGameOrchestrator : public AActor
{
	GENERATED_BODY()

public:
	AGameOrchestrator();

	UFUNCTION(BlueprintCallable)
	virtual void PrepareGame(int PlayerIndex);

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditInstanceOnly)
	APlayerSpawnPoint* Player1SpawnPoint;

	UPROPERTY(EditInstanceOnly)
	APlayerSpawnPoint* Player2SpawnPoint;

	UPROPERTY(EditInstanceOnly)
	UClass* PlayerClass;

	UPROPERTY(EditInstanceOnly)
	int InputDelay;

private:
	int FrameCount = 0;

	UPROPERTY()
	UPlayerInputProcessor* Player1InputProcessor;
	UPROPERTY()
	UPlayerInputProcessor* Player2InputProcessor;

	UPROPERTY()
	UGameSimulation* GameSimulation;

	void BindInputs(int PlayerIndex);
};
