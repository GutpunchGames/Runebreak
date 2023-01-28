// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/InputBuffer.h"

UInputBuffer::UInputBuffer() {
	FrameInputs.SetNumUninitialized(65535);
}

UInputBuffer::UInputBuffer(const FObjectInitializer& ObjectInitializer) {
	FrameInputs.SetNumUninitialized(65535);
}

UInputBuffer::~UInputBuffer() {
}

FInput UInputBuffer::GetInput(int Frame) {
	UE_LOG(LogTemp, Warning, TEXT("Fetching Frame: %d"), Frame)
	int DelayAdjustedFrame = Frame - Delay;
	if (DelayAdjustedFrame <= MostRecentFrame) {
		return FrameInputs[DelayAdjustedFrame];
	}
	else {
		return GetMostRecentInput();
	}
}

FInput UInputBuffer::GetMostRecentInput() {
	return GetInput(MostRecentFrame);
}

void UInputBuffer::AddInput(FInput Input) {
	FrameInputs[Input.Frame] = Input;
	MostRecentFrame = FMath::Max(Input.Frame, MostRecentFrame);
}
