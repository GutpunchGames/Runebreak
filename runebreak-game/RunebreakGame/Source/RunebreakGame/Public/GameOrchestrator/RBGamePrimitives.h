#pragma once

#include "CoreMinimal.h"
#include "RBGamePrimitives.generated.h"

// forward declarations
class URBGameSimulation;
class USimulationEntity;

USTRUCT(BlueprintType)
struct FPosition {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float x;

	UPROPERTY(BlueprintReadWrite)
	float y;
};

USTRUCT(BlueprintType)
struct FVelocity {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float dx;

	UPROPERTY(BlueprintReadWrite)
	float dy;
};

