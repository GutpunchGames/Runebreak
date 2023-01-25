// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerSpawnConfig.Generated.h"

UENUM(BlueprintType)
enum class PlayerClientType: uint8 {
	Local = 0x0,
	Remote = 0x1
};

USTRUCT(BlueprintType)
struct FPlayerSpawnConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	PlayerClientType ClientType;
	UPROPERTY(BlueprintReadWrite)
	FString RemoteHost;
	UPROPERTY(BlueprintReadWrite)
	int RemotePort;
};
