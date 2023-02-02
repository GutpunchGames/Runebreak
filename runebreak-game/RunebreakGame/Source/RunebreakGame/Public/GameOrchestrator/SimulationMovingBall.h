// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RunebreakGame/Public/GameOrchestrator/GameSimulation.h>
#include "GameOrchestrator/SimulationActor.h"
#include "SimulationMovingBall.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBREAKGAME_API ASimulationMovingBall : public ASimulationActor
{
	GENERATED_BODY()

public:
	virtual void SimulationTick(int Frame, IInputBuffer* Player1InputBuffer, IInputBuffer* Player2InputBuffer) override;
	FString SerializeState() override;
	virtual void Deserialize(const FString& Bytes) override;

	UPROPERTY()
	int PlayerIndex;
};
