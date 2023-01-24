// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStartParams.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RUNEBREAKGAME_API FGameStartParams
{
GENERATED_BODY()
public:
	FGameStartParams();
	~FGameStartParams();

	UPROPERTY(BlueprintReadWrite)
	bool IsHost;

	UPROPERTY(BlueprintReadWrite)
	FString HostIP;

	UFUNCTION(BlueprintCallable)
	FString ToString() {
		return FString::Printf(
			TEXT("isHost: %b -- hostIP: %s"), IsHost, *HostIP
		);
	}
};
