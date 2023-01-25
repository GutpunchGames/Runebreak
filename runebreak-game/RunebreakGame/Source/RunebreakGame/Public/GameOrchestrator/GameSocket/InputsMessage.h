// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputsMessage.generated.h"

USTRUCT(BlueprintType)
struct RUNEBREAKGAME_API FInputsMessage
{
	GENERATED_BODY()

public:
	int16 Frame;
	int8 Direction;

	FInputsMessage() {
		Frame = 0;
		Direction = 0;
	}

	static void ParseString(FString& Str, FInputsMessage& InputsMessage) {
		FString Left, Right;
		Str.Split(TEXT(","), &Left, &Right);
		InputsMessage.Frame = FCString::Atoi(*Left);
		InputsMessage.Direction = FCString::Atoi(*Right);
	}

	FString ToString() {
		return FString::Printf(TEXT("%d,%d"), Frame, Direction);
	}
};
