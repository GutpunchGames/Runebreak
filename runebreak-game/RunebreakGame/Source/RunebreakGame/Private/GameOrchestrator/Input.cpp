// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/Input.h"

FInput::FInput()
{
}

FString FInput::ToString() {
	return FString(
		+ "\tDirection: " + FString::FromInt(Direction)
	);
}
