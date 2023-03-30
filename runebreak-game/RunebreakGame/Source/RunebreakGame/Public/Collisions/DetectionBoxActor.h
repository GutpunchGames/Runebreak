// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RunebreakGame/Public/Collisions/DetectionBox.h>
#include "DetectionBoxActor.generated.h"

UCLASS()
class RUNEBREAKGAME_API ADetectionBoxActor : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetDetectionBox(const FDetectionBox& DetectionBox);

	UFUNCTION()
	void MarkInactive();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDetectionBox Box;
};
