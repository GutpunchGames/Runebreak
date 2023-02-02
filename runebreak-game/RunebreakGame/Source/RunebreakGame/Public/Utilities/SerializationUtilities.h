// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RUNEBREAKGAME_API SerializationUtilities
{
public:
	static FString SerializeFVector(const FVector& Vector);
	static FVector DeserializeFVector(const FString& Bytes);
};
