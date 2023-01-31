// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SaveState.h"

void USavedStateManager::Save(int Frame, TArray<ASimulationActor*> Actors) {
	UE_LOG(LogTemp, Warning, TEXT("Saved state for frame: %d"), Frame)
}

FSavedSimulation USavedStateManager::GetSavedState(int Frame) {
	return FSavedSimulation();
}
