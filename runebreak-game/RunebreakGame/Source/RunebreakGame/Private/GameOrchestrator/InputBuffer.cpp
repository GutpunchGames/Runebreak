// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/InputBuffer.h"

UInputBuffer::UInputBuffer() {
	Inputs.SetNumUninitialized(65535);
	EarliestDiscrepancy = -1;
}

UInputBuffer::UInputBuffer(const FObjectInitializer& ObjectInitializer) {
	Inputs.SetNumUninitialized(65535);
	EarliestDiscrepancy = -1;
}

UInputBuffer::~UInputBuffer() {
}

FInput UInputBuffer::GetInput(int Frame) {
	UE_LOG(LogTemp, Warning, TEXT("Fetching Frame: %d"), Frame)
	if (Frame <= MostRecentVerifiedFrame) {
		return Inputs[Frame];
	}
	else {
		return Inputs[MostRecentVerifiedFrame];
	}
}

FInput UInputBuffer::GetMostRecentInput() {
	return GetInput(MostRecentVerifiedFrame);
}

int UInputBuffer::ConsumeDiscrepancy() {
	int Result = EarliestDiscrepancy;
	EarliestDiscrepancy = -1;
	return Result;
}

void UInputBuffer::AddLocalInput(FInput Input) {
	Inputs[Input.Frame] = Input;
	MostRecentVerifiedFrame = FMath::Max(Input.Frame, MostRecentVerifiedFrame);
}

// we may be adding inputs for frames that have already executed
int UInputBuffer::AddRemoteInputs(TArray<FInput> NewInputs) {
	if (NewInputs.Num() <= 0) {
		return MostRecentVerifiedFrame;
	}
	FInput LastNewInput = NewInputs[NewInputs.Num() - 1];
	if (LastNewInput.Frame <= MostRecentVerifiedFrame) {
		// these are old inputs we already have
		return MostRecentVerifiedFrame;
	}

	int ValidInputsFrame = MostRecentVerifiedFrame;
	FInput LastVerifiedInput = Inputs[MostRecentVerifiedFrame];
	bool DidFindDiscrepancy = false;

	for (int i = 0; i < NewInputs.Num(); i++) {
		FInput NewInput = NewInputs[i];
		
		if (NewInput.MoveDirection != LastVerifiedInput.MoveDirection) {
			// we have detected a difference in the new input and the latest verified input, so a prediction would be wrong!
			DidFindDiscrepancy = true;
			if (EarliestDiscrepancy == -1 || EarliestDiscrepancy > NewInput.Frame) {
				EarliestDiscrepancy = NewInput.Frame;
			}
		}
		else if (!DidFindDiscrepancy) {
			// if we haven't found a discrepancy yet in what would have been our predictions, we can increment this
			ValidInputsFrame++;
		}

		Inputs[NewInput.Frame] = NewInput;
		MostRecentVerifiedFrame = NewInput.Frame;
	}
	return ValidInputsFrame;
}

TArray<FInput> UInputBuffer::GetInputsSince(int FrameExclusive) {
	TArray<FInput> Result;
	if (FrameExclusive <= -1 || FrameExclusive > MostRecentVerifiedFrame) {
		return Result;
	}

	for (int i = FrameExclusive + 1; i <= MostRecentVerifiedFrame; i++) {
		Result.Emplace(Inputs[i]);
	}

	return Result;
}
