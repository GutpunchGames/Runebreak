// Fill out your copyright notice in the Description page of Project Settings.


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
	return Inputs[Frame];
}

FInput ULocalInputBuffer::GetMostRecentInput() {
	return GetInput(LatestFrame);
}

void ULocalInputBuffer::AddInput(FInput Input) {
	Inputs[Input.Frame] = Input;
	LatestFrame = FMath::Max(Input.Frame, LatestFrame);
}

TArray<FInput> ULocalInputBuffer::GetInputsSince(int FrameExclusive) {
	TArray<FInput> Result;
	if (FrameExclusive <= -1 || FrameExclusive > LatestFrame) {
		return Result;
	}

	for (int i = FrameExclusive + 1; i <= LatestFrame; i++) {
		Result.Emplace(Inputs[i]);
	}

	return Result;
}
