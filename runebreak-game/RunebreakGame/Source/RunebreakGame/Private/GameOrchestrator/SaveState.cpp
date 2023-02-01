// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SaveState.h"
#include "Misc/Base64.h"

void USavedStateManager::Save(int Frame, TArray<ASimulationActor*> Actors) {
	UE_LOG(LogTemp, Warning, TEXT("Saved state for frame: %d"), Frame)

		FSavedSimulation SavedSimulation;
		SavedSimulation.Frame = Frame;

		for (ASimulationActor* SimulationActor : Array)
		{
			SimulationActor->WriteFunc()
		}
}

FSavedSimulation USavedStateManager::GetSavedState(int Frame) {
	return FSavedSimulation();
}
