#include "GameOrchestrator/InputBuffer/LocalInputBuffer.h"

ULocalInputBuffer::ULocalInputBuffer() {
	Inputs.SetNumUninitialized(65535);
}

ULocalInputBuffer::ULocalInputBuffer(const FObjectInitializer& ObjectInitializer) {
	Inputs.SetNumUninitialized(65535);
}

ULocalInputBuffer::~ULocalInputBuffer() {
}

FInput ULocalInputBuffer::GetInput(int Frame) {
	// with a delay, the first <delay> frames will be invalid.
	if (Frame < Delay) {
		FInput SyntheticInput;
		SyntheticInput.Frame = Frame;
		SyntheticInput.MoveDirection = 0;
		return SyntheticInput;
	}
	return Inputs[Frame];
}

void ULocalInputBuffer::AddInput(FInput Input) {
	int DelayAdjustedFrame = Input.Frame + Delay;
	Input.Frame = DelayAdjustedFrame;
	Inputs[DelayAdjustedFrame] = Input;
	LatestFrame = DelayAdjustedFrame;
}

TArray<FInput> ULocalInputBuffer::GetInputsSince(int FrameExclusive) {
	TArray<FInput> Result;
	if (FrameExclusive <= -1 || FrameExclusive > LatestFrame) {
		return Result;
	}

	for (int i = FrameExclusive + 1; i <= LatestFrame; i++) {
		Result.Emplace(GetInput(i));
	}

	return Result;
}
