#include "GameOrchestrator/InputBuffer/RemoteInputBuffer.h"

URemoteInputBuffer::URemoteInputBuffer() {
	Inputs.SetNumUninitialized(65535);
	EarliestDiscrepancy = -1;
}

URemoteInputBuffer::URemoteInputBuffer(const FObjectInitializer& ObjectInitializer) {
	Inputs.SetNumUninitialized(65535);
	EarliestDiscrepancy = -1;
}

URemoteInputBuffer::~URemoteInputBuffer() {
}

FInput URemoteInputBuffer::GetInput(int Frame) {
	if (Frame <= MostRecentVerifiedFrame) {
		return Inputs[Frame];
	}
	else {
		// fill in with a prediction for now, based on what we were most recently doing
		Inputs[Frame] = Inputs[MostRecentVerifiedFrame];
		return Inputs[Frame];
	}
}

int URemoteInputBuffer::ConsumeDiscrepancy() {
	int Result = EarliestDiscrepancy;
	EarliestDiscrepancy = -1;
	return Result;
}

// we may be adding inputs for frames that have already executed
void URemoteInputBuffer::AddRemoteInputs(TArray<FInput> NewInputs) {
	if (NewInputs.Num() <= 0) {
		return;
	}
	FInput LastNewInput = NewInputs[NewInputs.Num() - 1];
	if (LastNewInput.Frame <= MostRecentVerifiedFrame) {
		// these are all old inputs we already have
		return;
	}

	FInput LastVerifiedInput = Inputs[MostRecentVerifiedFrame];

	for (int i = 0; i < NewInputs.Num(); i++) {
		if (NewInputs[i].Frame <= MostRecentVerifiedFrame) {
			// old input, don't need to do anything
			continue;
		}

		FInput NewInput = NewInputs[i];
		if (NewInput.MoveDirection != LastVerifiedInput.MoveDirection) {
			// we have detected a difference in the new input and the latest verified input, so a prediction would be wrong!
			if (EarliestDiscrepancy == -1 || EarliestDiscrepancy > NewInput.Frame) {
				EarliestDiscrepancy = NewInput.Frame;
			}
		}

		Inputs[NewInput.Frame] = NewInput;
		MostRecentVerifiedFrame = NewInput.Frame;
	}
}
