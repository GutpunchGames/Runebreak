// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOrchestrator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RUNEBREAKGAME_API AGameOrchestrator : public AActor
{
	GENERATED_BODY()

public:
	AGameOrchestrator();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	int frameCount = 0;
	virtual void HandleMoveUp();
};
