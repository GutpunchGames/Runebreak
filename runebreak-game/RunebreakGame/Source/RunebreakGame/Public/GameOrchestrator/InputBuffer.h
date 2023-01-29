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

	UFUNCTION()
	void AddLocalInput(FInput Input);

	UFUNCTION()
	// returns the most recent frame for which there was no discrepancy between the predicted inputs and the
	// actual inputs. If this frame is less than the current executing frame, then we need to do a rollback.
	int AddRemoteInputs(TArray<FInput> NewInputs);

	UFUNCTION()
	FInput GetInput(int Frame);

	UFUNCTION()
	FInput GetMostRecentInput();

	UFUNCTION()
	TArray<FInput> GetInputsSince(int FrameExclusive);

	UFUNCTION()
	int ConsumeDiscrepancy();

private:
	UPROPERTY()
	TArray<FInput> Inputs;

	UPROPERTY()
	int MostRecentVerifiedFrame = 0;

	UPROPERTY()
	int InputBufferSize = 0;

	UPROPERTY()
	int EarliestDiscrepancy;
};
