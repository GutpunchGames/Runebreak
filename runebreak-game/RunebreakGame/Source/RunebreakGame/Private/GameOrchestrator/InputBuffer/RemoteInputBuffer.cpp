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
	UE_LOG(LogTemp, Warning, TEXT("Fetching Frame: %d"), Frame)
	if (Frame <= MostRecentVerifiedFrame) {
		return Inputs[Frame];
	}
	else {
		// make a prediction
		return Inputs[MostRecentVerifiedFrame];
	}
}

//FInput URemoteInputBuffer::GetMostRecentInput() {
//	return GetInput(MostRecentVerifiedFrame);
//}

int URemoteInputBuffer::ConsumeDiscrepancy() {
	int Result = EarliestDiscrepancy;
	EarliestDiscrepancy = -1;
	return Result;
}

// we may be adding inputs for frames that have already executed
int URemoteInputBuffer::AddRemoteInputs(TArray<FInput> NewInputs) {
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
