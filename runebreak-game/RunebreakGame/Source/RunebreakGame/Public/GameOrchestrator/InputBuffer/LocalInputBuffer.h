// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameOrchestrator/Input.h"
#include "LocalInputBuffer.generated.h"

UCLASS()
class RUNEBREAKGAME_API ULocalInputBuffer : public UObject
{
	GENERATED_BODY()

public:
	ULocalInputBuffer();
	ULocalInputBuffer(const FObjectInitializer& ObjectInitializer);
	~ULocalInputBuffer();

	UPROPERTY()
	int Delay = 0;

	UFUNCTION()
	void AddInput(FInput Input);

	UFUNCTION()
	FInput GetInput(int Frame);

	UFUNCTION()
	FInput GetMostRecentInput();

	UFUNCTION()
	TArray<FInput> GetInputsSince(int FrameExclusive);

private:
	UPROPERTY()
	TArray<FInput> Inputs;

	UPROPERTY()
	int LatestFrame = 0;
};
