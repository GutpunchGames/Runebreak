// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include "RunebreakAPI.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBREAKGAME_API URunebreakAPI : public UObject
{
	GENERATED_BODY()

public:
	URunebreakAPI();

	UFUNCTION(BlueprintCallable)
	void DoThing();

	UFUNCTION(BlueprintCallable)
	void Login();

	UFUNCTION(BlueprintCallable)
	void TestJsonSerialization();

	void OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
