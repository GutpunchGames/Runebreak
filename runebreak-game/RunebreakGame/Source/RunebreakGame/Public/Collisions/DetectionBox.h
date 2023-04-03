// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameOrchestrator/RBGamePrimitives.h"
#include "Engine/DataTable.h"
#include "DetectionBox.generated.h"

UENUM()
enum DetectionBoxType {
	Hitbox		UMETA(DisplayName = "Hitbox"),
	Hurtbox		UMETA(DisplayName = "Hurtbox"),
	Collision	UMETA(DisplayName = "Collision Box"),
	Inactive	UMETA(DisplayName = "Inactive Box")
};

USTRUCT(BlueprintType)
struct FDetectionBoxDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Offset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int StartFrame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<DetectionBoxType> Type = DetectionBoxType::Inactive;
};

USTRUCT(BlueprintType)
struct FDetectionBoxConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Offset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<DetectionBoxType> Type = DetectionBoxType::Inactive;
};

// this is the actual runtime detection box
USTRUCT(BlueprintType)
struct FDetectionBox 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<DetectionBoxType> Type = DetectionBoxType::Inactive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 OwnerId;
};

USTRUCT(BlueprintType)
struct FFrameDetectionBoxConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FDetectionBoxConfig> DetectionBoxes;
};

USTRUCT(BlueprintType)
struct FStateDetectionBoxConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FFrameDetectionBoxConfig> DetectionBoxesByFrame;
};

UCLASS()
class UDetectionBoxLoader : public UObject
{
	GENERATED_BODY()

public:
	FStateDetectionBoxConfig LoadDetectionBoxConfigs(int NumFrames, UDataTable* DataTable);
};
