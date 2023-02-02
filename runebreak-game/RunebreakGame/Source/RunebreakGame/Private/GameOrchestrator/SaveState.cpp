// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SaveState.h"
#include <Utilities/Base64Utilities.h>

//To do: 
//1. Created saved actors
//2. Add saved actors to simulation snapshot
//3. Add snapshot to map
void USavedStateManager::Save(int Frame, TArray<ASimulationActor*> Actors) {

		FSavedSimulation SavedSimulation;
		SavedSimulation.Frame = Frame;

		FString ConcatenatedActors;
		for (ASimulationActor* SimulationActor : Actors)
		{
			const FString SerializedActor = SimulationActor->SerializeState();
			ConcatenatedActors += SerializedActor;
		}
		const FString Checksum = Base64Utilities::Base64Encode(ConcatenatedActors);
		UE_LOG(LogTemp, Warning, TEXT("Saved state for frame: %d -- %s"), Frame, *Checksum);
}

FSavedSimulation USavedStateManager::GetSavedState(int Frame) {
	return FSavedSimulation();
}
