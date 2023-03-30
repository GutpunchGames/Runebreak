// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameOrchestrator/RBGamePrimitives.h"
#include "DetectionBox.generated.h"

UENUM()
enum DetectionBoxType {
	Hitbox		UMETA(DisplayName = "Hitbox"),
	Hurtbox		UMETA(DisplayName = "Hurtbox"),
	Collision	UMETA(DisplayName = "Collision Box"),
	Inactive	UMETA(DisplayName = "Inactive Box")
};

USTRUCT(BlueprintType)
struct FDetectionBox
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPosition Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<DetectionBoxType> Type = DetectionBoxType::Inactive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 OwnerId;
};
