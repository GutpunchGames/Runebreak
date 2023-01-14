// Fill out your copyright notice in the Description page of Project Settings.


#include "Sandbox/SandboxBPFunctionLibrary.h"
#include "Sandbox/RestCallExperiments.h"
#include "Sandbox/FunctionPointerExamples.h"

bool USandboxBPFunctionLibrary::FunctionWithCallback(FExampleDelegate Out) {
	Out.ExecuteIfBound("output string");
	return false;
}

bool USandboxBPFunctionLibrary::AsyncFunctionWithCallback(FExampleDelegate Out) {
	AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [Out]() {
		 // schedule back to the main thread
		AsyncTask(ENamedThreads::GameThread, [Out]() {
			// execute the delegate along with the param
			Out.ExecuteIfBound("async emission");
		});
	});

	return true;
}

bool USandboxBPFunctionLibrary::DoTFunctionRefExample() {
	DoSomethingWithConvertingStringsToInts([](FString Str) {
		if (Str.Equals("one")) {
			return 1;
		}
		else if (Str.Equals("two")) {
			return 2;
		}
		else if (Str.Equals("three")) {
			return 3;
		}
		else {
			return -1;
		}
	});

	FunctionWithVoidCallback([]() {
		UE_LOG(LogTemp, Warning, TEXT("void callback"))
	});

	return true;
}

void USandboxBPFunctionLibrary::DoTestLoginCall(FString username, FString password) {
	_DoTestLoginCall(username, password,
		[]() {
			UE_LOG(LogTemp, Warning, TEXT("On Success"))
		},
		[]() {
			UE_LOG(LogTemp, Warning, TEXT("On Failure"))
		});
}