// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/Input.h"

FInput::FInput()
{
	Frame = -1;
	MoveDirection = 0;
}

FString FInput::ToString() {
	return FString("Direction: " + FString::FromInt(MoveDirection));
}
