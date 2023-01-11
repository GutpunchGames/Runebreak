// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SandboxBPFunctionLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FExampleDelegate, FString, StringOut);

/**
 * 
 */
UCLASS()
class RUNEBREAKGAME_API USandboxBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// A simple function with a callback FExampleDelegate.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Sandbox")
	static bool FunctionWithCallback(FExampleDelegate Out);

	// An asynchronous function with a callback FExampleDelegate.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Sandbox")
	static bool AsyncFunctionWithCallback(FExampleDelegate Out);
};
