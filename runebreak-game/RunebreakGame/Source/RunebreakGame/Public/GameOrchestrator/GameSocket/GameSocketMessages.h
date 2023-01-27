// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSocketMessages.generated.h"

USTRUCT(BlueprintType)
struct FPingMessage {
	GENERATED_BODY()

public:
	UPROPERTY()
	FString OriginTimestamp;

	UPROPERTY()
	int OriginFrame;
};

USTRUCT(BlueprintType)
struct FPongMessage {
	GENERATED_BODY()

public:
	UPROPERTY()
	FString OriginTimestamp;

	UPROPERTY()
	int RemoteFrame;
};

