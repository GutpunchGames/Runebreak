// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input.generated.h"

USTRUCT()
struct RUNEBREAKGAME_API FInput
{
	GENERATED_BODY()

public:
	FInput();

	int Direction;

	FString ToString();
};
