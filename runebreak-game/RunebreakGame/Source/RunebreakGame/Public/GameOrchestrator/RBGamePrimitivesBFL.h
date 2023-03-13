// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameOrchestrator/RBGamePrimitives.h"
#include "Math/TransformNonVectorized.h"
#include "RBGamePrimitivesBFL.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBREAKGAME_API URBGamePrimitivesBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static void ToTransform(const FPosition& Position, FTransform& Transform);
};
