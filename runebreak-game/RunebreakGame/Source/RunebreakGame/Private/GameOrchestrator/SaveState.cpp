// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SaveState.h"
#include "Misc/SecureHash.h"
#include <Utilities/Base64Utilities.h>

FString USavedStateManager::Save(int Frame, TArray<ASimulationActor*> Actors) {
		FSavedSimulation SavedSimulation;
		SavedSimulation.Frame = Frame;

		// todo: delete this ConcatenatedActors mechanism (for perf). should be computed based on raw bytes
		// in SavedSimulation
		FString ConcatenatedActors;
		for (ASimulationActor* SimulationActor : Actors)
		{
			FSavedActor SavedActor;
			SavedActor.ActorId = SimulationActor->ActorId;
			SavedActor.ActorType = "Test-Type"; // todo: use this
			FString SerializedState = SimulationActor->SerializeState();
			ConcatenatedActors += SerializedState;
			SavedActor.Data = SerializedState;
			SavedSimulation.Actors.Add(SavedActor);
		}
		SavedSimulation.ComputeChecksum(ConcatenatedActors);
		SavedStates.Add(Frame, SavedSimulation);
		return SavedSimulation.Checksum;
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

void FSavedSimulation::ComputeChecksum(const FString& SerializedActors) {
	FString ActorsChecksum = FMD5::HashAnsiString(*SerializedActors);
	Checksum = FString::Printf(TEXT("%d>%s"), Frame, *(FMD5::HashAnsiString(*SerializedActors)));
}
