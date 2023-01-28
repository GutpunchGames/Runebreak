// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/CircularBuffer.h"
#include "GameOrchestrator/Input.h"
#include "Templates/SharedPointer.h"
#include "InputBuffer.generated.h"

UCLASS()
class RUNEBREAKGAME_API UInputBuffer : public UObject
{
	GENERATED_BODY()

public:
	UInputBuffer();
	UInputBuffer(const FObjectInitializer& ObjectInitializer);
	~UInputBuffer();

	UPROPERTY()
	int Delay = 0;

	void AddInput(FInput Input);
	FInput GetInput(int Frame);
	FInput GetMostRecentInput();

private:
	UPROPERTY()
	TArray<FInput> FrameInputs;

	UPROPERTY()
	int MostRecentFrame = 0;
};
