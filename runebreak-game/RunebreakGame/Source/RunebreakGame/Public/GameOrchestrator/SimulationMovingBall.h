// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/SimulationActor.h"
#include "SimulationMovingBall.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBREAKGAME_API ASimulationMovingBall : public ASimulationActor
{
	GENERATED_BODY()

	void SimulationTick(int MoveDirection) override;
	FString SerializeState() override;
};
