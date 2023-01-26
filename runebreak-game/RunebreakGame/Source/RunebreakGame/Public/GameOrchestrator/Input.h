// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input.generated.h"

USTRUCT()
struct FInput
{
	GENERATED_BODY()

public:
	FInput();

	UPROPERTY()
	int MoveDirection;

	FString ToString();
};
