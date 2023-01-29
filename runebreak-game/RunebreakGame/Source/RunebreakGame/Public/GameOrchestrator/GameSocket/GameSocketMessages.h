// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include "GameSocketMessages.generated.h"

USTRUCT(BlueprintType)
struct FPingMessage {
	GENERATED_BODY()

public:
	UPROPERTY()
	FString OriginTimestamp;
};

USTRUCT(BlueprintType)
struct FPongMessage {
	GENERATED_BODY()

public:
	UPROPERTY()
	FString OriginTimestamp;
};

USTRUCT(BlueprintType)
struct FSyncMessage {
	GENERATED_BODY()

public:
	UPROPERTY()
	int OriginFrame;
	UPROPERTY()
	TArray<FInput> RecentInputs; // todo: make array of unacked inputs
	UPROPERTY()
	int FrameAck;
};

