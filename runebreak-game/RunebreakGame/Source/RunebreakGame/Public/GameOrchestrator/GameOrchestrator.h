// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOrchestrator/PlayerSpawnConfig.h"
#include"GameOrchestrator/GameSocket/InputsMessage.h"
#include <RunebreakGame/Public/GameOrchestrator/PlayerSpawnPoint.h>
#include <RunebreakGame/Public/GameOrchestrator/PlayerInputProcessor.h>
#include <RunebreakGame/Public/GameOrchestrator/GameSimulation.h>
#include <RunebreakGame/Public/GameOrchestrator/SaveState.h>
#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/RBGameSocket.h>
#include "GameOrchestrator/GameLogger/GameLogger.h"
#include "GameOrchestrator.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnFrameAdvanced);

UCLASS(Blueprintable)
class RUNEBREAKGAME_API AGameOrchestrator : public AActor
{
	GENERATED_BODY()

public:
	AGameOrchestrator();

	UFUNCTION(BlueprintCallable)
	virtual void PrepareGame(FPlayerSpawnConfig Player1SpawnConfig, FPlayerSpawnConfig Player2SpawnConfig, int LocalPort, int InputDelay);

	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditInstanceOnly)
	UClass* PlayerClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ARBGameSocket* GameSocket;

	UPROPERTY(EditInstanceOnly)
	bool LogSocketMessages;

	UPROPERTY(BlueprintReadWrite)
	FOnFrameAdvanced OnFrameAdvancedDelegate;

	UPROPERTY(BlueprintReadOnly)
	UGameSimulation* GameSimulation;

	UPROPERTY(BlueprintReadOnly)
	bool IsAnyPlayerRemote;

private:
	UPROPERTY()
	UGameLogger* GameLogger;

	UPROPERTY()
	USavedStateManager* SavedStateManager;

	UPROPERTY()
	UPlayerInputProcessor* Player1InputProcessor;
	UPROPERTY()
	UPlayerInputProcessor* Player2InputProcessor;

	UPROPERTY()
	bool IsPlayer1Remote;
	UPROPERTY()
	bool IsPlayer2Remote;

	UPROPERTY()
	bool IsCorrectingRift;

	UPROPERTY()
	float RiftPauseThresholdFrames = 4;

	UFUNCTION()
	float ComputeRift();

	UFUNCTION()
	void HandleSyncMessage(const FSyncMessage& SyncMessage);
};
