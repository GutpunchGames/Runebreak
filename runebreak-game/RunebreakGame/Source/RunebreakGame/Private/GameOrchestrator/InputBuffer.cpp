// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/InputBuffer.h"

UInputBuffer::UInputBuffer() {
}

UInputBuffer::~UInputBuffer() {
}

FInput UInputBuffer::GetInput(int Frame) {
	if (Frame - Delay >= 0) {
		return FrameInputs[Frame - Delay];
	}
	else {
		FInput ret;
		return ret;
	}
}

FInput UInputBuffer::GetMostRecentInput() {
	return GetInput(FrameInputs.Num() - 1);
}

void UInputBuffer::AddInput(FInput FrameInput) {
	// todo: this should be one trillion times more efficient
	FrameInputs.Emplace(FrameInput);
}
