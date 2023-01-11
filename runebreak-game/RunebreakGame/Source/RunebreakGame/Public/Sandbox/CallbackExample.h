// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CallbackExample.generated.h"

UCLASS(Blueprintable)
class RUNEBREAKGAME_API UCallbackExample : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void DoThing();
};
