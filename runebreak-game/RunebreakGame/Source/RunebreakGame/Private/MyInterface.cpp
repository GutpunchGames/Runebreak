// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInterface.h"
#include <string>

// Add default functionality here for any IMyInterface functions that are not pure virtual.

void IMyInterface::TestDefaultImpl() {
	UE_LOG(LogTemp, Warning, TEXT("TestDefaultImpl"));
}

bool IMyInterface::DoThing(std::string testArg) {
	UE_LOG(LogTemp, Warning, TEXT("DoThing called"));
	return true;
}
