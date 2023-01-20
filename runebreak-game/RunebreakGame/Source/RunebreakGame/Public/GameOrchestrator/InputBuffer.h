// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/RingBuffer.h"
#include "GameOrchestrator/Input.h"
#include "InputBuffer.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBREAKGAME_API UInputBuffer : public UObject
{
	GENERATED_BODY()

public:
	UInputBuffer();
	~UInputBuffer();

	int Delay = 0;

	void AddInput(FInput FrameInput);
	FInput GetInput(int frame);
	FInput GetMostRecentInput();

private:
	// todo: use ring buffer
	TArray<FInput> FrameInputs;
};
