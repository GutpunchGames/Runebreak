#pragma once

#include "CoreMinimal.h"
#include "RBGamePrimitives.generated.h"

// forward declaration
class URBGameSimulation;

USTRUCT()
struct FPosition {
	GENERATED_BODY()

	UPROPERTY()
	double x;

	UPROPERTY()
	double y;
};

USTRUCT()
struct FVelocity {
	GENERATED_BODY()

	UPROPERTY()
	double dx;

	UPROPERTY()
	double dy;
};

