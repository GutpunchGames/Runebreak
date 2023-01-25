// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOrchestrator/PlayerSpawnConfig.h"
#include"GameOrchestrator/GameSocket/InputsMessage.h"
#include <RunebreakGame/Public/GameOrchestrator/PlayerSpawnPoint.h>
#include <RunebreakGame/Public/GameOrchestrator/PlayerInputProcessor.h>
#include <RunebreakGame/Public/GameOrchestrator/GameSimulation.h>
#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/RBGameSocket.h>
#include "GameOrchestrator.generated.h"

UCLASS(Blueprintable)
class RUNEBREAKGAME_API AGameOrchestrator : public AActor
{
	GENERATED_BODY()

public:
	AGameOrchestrator();

	UFUNCTION(BlueprintCallable)
	virtual void PrepareGame(FPlayerSpawnConfig Player1SpawnConfig, FPlayerSpawnConfig Player2SpawnConfig, int LocalPort);

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditInstanceOnly)
	UClass* PlayerClass;

	UPROPERTY(EditInstanceOnly)
	int InputDelay;

	UPROPERTY(BlueprintReadOnly)
	URBGameSocket* GameSocket;

	UPROPERTY(EditInstanceOnly)
	bool LogSocketMessages;

private:
	int FrameCount = 0;

	UPROPERTY()
	UPlayerInputProcessor* Player1InputProcessor;
	UPROPERTY()
	UPlayerInputProcessor* Player2InputProcessor;

	UPROPERTY()
	UGameSimulation* GameSimulation;

	void HandleRemoteInputsReceived(const FInputsMessage& InputsMessage);

	bool IsPlayer1Remote;
	bool IsPlayer2Remote;
};
