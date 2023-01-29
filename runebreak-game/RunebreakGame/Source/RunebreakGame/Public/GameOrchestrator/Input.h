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
	int Frame;

	UPROPERTY()
	int MoveDirection;

	FString ToString();

	bool operator==(const FInput& other)
	{
		return Frame == other.Frame && MoveDirection == other.MoveDirection;
	}
};
