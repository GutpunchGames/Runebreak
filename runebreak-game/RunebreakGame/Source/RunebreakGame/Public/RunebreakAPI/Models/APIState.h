// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APIState.generated.h"

UENUM(BlueprintType)
enum class EConnectionStatus: uint8
{
	Uninitialized = 0x0,
	Connecting = 0x1,
	Connected = 0x2
};

USTRUCT()
struct FApiState
{
	GENERATED_BODY()
public:
	UPROPERTY()
		FString authToken;

	UPROPERTY()
		EConnectionStatus connectionStatus;

	FString ToString() {
		return FString(
			+ "\tauthToken: " + authToken + "\n"
			+ "\thello second line: " + "poop" + '\n'
		);
	}
};
