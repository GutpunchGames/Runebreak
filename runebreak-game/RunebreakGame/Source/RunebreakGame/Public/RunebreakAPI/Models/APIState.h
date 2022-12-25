// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include<string>
#include "CoreMinimal.h"
#include "APIState.generated.h"

UENUM(BlueprintType)
enum class EConnectionStatus: uint8
{
	Uninitialized = 0x0,
	Connecting = 0x1,
	Connected = 0x2
};


USTRUCT(BlueprintType)
struct FApiState
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString authToken;

	UPROPERTY(BlueprintReadWrite)
		EConnectionStatus connectionStatus;
};

///**
// * 
// */
//class RUNEBREAKGAME_API APIState
//{
//public:
//	APIState();
//	~APIState();
//};
