// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SaveState.h"
#include <Utilities/Base64Utilities.h>

//To do: 
//1. Created saved actors
//2. Add saved actors to simulation snapshot
FString USavedStateManager::Save(int Frame, TArray<ASimulationActor*> Actors) {
		FSavedSimulation SavedSimulation;
		SavedSimulation.Frame = Frame;

		FString ConcatenatedActors;
		for (ASimulationActor* SimulationActor : Actors)
		{
			const FString SerializedActor = SimulationActor->SerializeState();
			ConcatenatedActors += SerializedActor;
		}
		const FString Checksum = Base64Utilities::Base64Encode(ConcatenatedActors);
		SavedSimulation.Checksum = Checksum;
		SavedStates.Add(Frame, SavedSimulation);
		return Checksum;
}

FSavedSimulation USavedStateManager::GetSavedState(int Frame) {
	if (SavedStates.Contains(Frame)) {
		return SavedStates[Frame];
	}
	else {
		FSavedSimulation InvalidSimulation;
		InvalidSimulation.Frame = -1;
		InvalidSimulation.Checksum = "INVALID";
		return InvalidSimulation;
	}
}
