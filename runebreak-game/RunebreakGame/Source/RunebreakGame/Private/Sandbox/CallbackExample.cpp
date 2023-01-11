// Fill out your copyright notice in the Description page of Project Settings.


#include "Sandbox/CallbackExample.h"

void UCallbackExample::DoThing() {
	UE_LOG(LogTemp, Warning, TEXT("CallbackExample: DoThing() START"))
	UE_LOG(LogTemp, Warning, TEXT("CallbackExample: DoThing() END"))
}
