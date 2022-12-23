// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <RunebreakGame/Public/RunebreakAPI/RunebreakAPI.h>
#include <RunebreakGame/Public/TestObject/TestObject.h>
#include "RunebreakGameInstance.generated.h"

UCLASS()
class RUNEBREAKGAME_API URunebreakGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URunebreakGameInstance();

	UPROPERTY(BlueprintReadWrite)
	URunebreakAPI* api;
};