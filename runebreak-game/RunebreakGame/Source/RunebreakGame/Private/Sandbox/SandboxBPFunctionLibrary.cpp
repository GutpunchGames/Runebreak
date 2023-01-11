// Fill out your copyright notice in the Description page of Project Settings.


#include "Sandbox/SandboxBPFunctionLibrary.h"

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

