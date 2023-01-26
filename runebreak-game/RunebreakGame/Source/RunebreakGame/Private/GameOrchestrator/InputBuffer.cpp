// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/InputBuffer.h"

UInputBuffer::UInputBuffer() {
	FrameIndex = 0;
	FrameInputs.SetNumUninitialized(512);
}

UInputBuffer::UInputBuffer(const FObjectInitializer& ObjectInitializer) {
	FrameIndex = 0;
	FrameInputs.SetNumUninitialized(512);
}

UInputBuffer::~UInputBuffer() {
}

FInput UInputBuffer::GetInput(int Frame) {
	UE_LOG(LogTemp, Warning, TEXT("Fetching Frame: %d"), Frame)
	int DelayAdjustedFrame = Frame - Delay;
	int TargetIndex = DelayAdjustedFrame % 512;
	if (FrameInputs.IsValidIndex(TargetIndex)) {
		return FrameInputs[TargetIndex];
	}
	else {
		return FInput();
	}
}

FInput UInputBuffer::GetMostRecentInput() {
	return GetInput(FrameIndex - 1);
}

void UInputBuffer::AddInput(FInput Input) {
	UE_LOG(LogTemp, Warning, TEXT("Adding input for frame: %ld"), FrameIndex)
	FrameInputs[FrameIndex % 512] = Input;
	FrameIndex++;
	UE_LOG(LogTemp, Warning, TEXT("post-increment frame index is now: %ld"), FrameIndex)
}
