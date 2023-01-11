// Fill out your copyright notice in the Description page of Project Settings.


#include "Sandbox/FunctionPointerExamples.h"

FunctionPointerExamples::FunctionPointerExamples()
{
}

FunctionPointerExamples::~FunctionPointerExamples()
{
}

void DoSomethingWithConvertingStringsToInts(TFunctionRef<int32(const FString& Str)> Convert) {
	FString strs[4] = { "one", "two", "three", "four"};
	UE_LOG(LogTemp, Warning, TEXT("calling method"))
	for (const FString& Str : strs) {
		int32 Int = Convert(Str);
		UE_LOG(LogTemp, Warning, TEXT("converted int: %i"), Int)
	}
}

void FunctionWithVoidCallback(TFunctionRef<void()> Callback) {
	Callback();
	Callback();
	Callback();
}
