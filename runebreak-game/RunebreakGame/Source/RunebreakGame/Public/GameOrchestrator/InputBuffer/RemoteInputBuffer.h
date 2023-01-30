// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/CircularBuffer.h"
#include "GameOrchestrator/Input.h"
#include "GameOrchestrator/InputBuffer.h"
#include "Templates/SharedPointer.h"
#include "RemoteInputBuffer.generated.h"

UCLASS()
class RUNEBREAKGAME_API URemoteInputBuffer : public UObject, public IInputBuffer
{
	GENERATED_BODY()

public:
	URemoteInputBuffer();
	URemoteInputBuffer(const FObjectInitializer& ObjectInitializer);
	~URemoteInputBuffer();

	UPROPERTY()
	int Delay = 0;

	UFUNCTION()
	// returns the most recent frame for which there was no discrepancy between the predicted inputs and the
	// actual inputs. If this frame is less than the current executing frame, then we need to do a rollback.
	int AddRemoteInputs(TArray<FInput> NewInputs);

	virtual FInput GetInput(int Frame) override;

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
