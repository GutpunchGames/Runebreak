// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObject/TestObject.h"

UTestObject::UTestObject() {
	UE_LOG(LogTemp, Warning, TEXT("findme: TestObject instantiated"));
}

void UTestObject::DoThing() {
	UE_LOG(LogTemp, Warning, TEXT("findme: DoThing() called in TestObject"));
}
