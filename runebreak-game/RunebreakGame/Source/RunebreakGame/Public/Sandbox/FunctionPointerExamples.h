// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RUNEBREAKGAME_API FunctionPointerExamples
{
public:
	FunctionPointerExamples();
	~FunctionPointerExamples();
};

void DoSomethingWithConvertingStringsToInts(TFunctionRef<int32(const FString& Str)> Convert);

void FunctionWithVoidCallback(TFunctionRef<void()> Convert);
