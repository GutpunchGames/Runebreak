// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <RunebreakGame/Public/GameOrchestrator/SimulationActor.h>
#include "SaveState.generated.h"

USTRUCT()
struct RUNEBREAKGAME_API FSavedActor
{
	GENERATED_BODY()

public:
	int ActorId;
	FString ActorType;
	FString Data;
};

USTRUCT()
struct RUNEBREAKGAME_API FSavedSimulation
{
	GENERATED_BODY()
public:
	TArray<FSavedActor> Actors;
	FString Checksum;
	int Frame;

	void ComputeChecksum(const FString& SerializedActors);
};

UCLASS()
class RUNEBREAKGAME_API USavedStateManager : public UObject
{
	GENERATED_BODY()

public:
	// returns checksum
	FString Save(int Frame, TArray<ASimulationActor*> Actors);
	FSavedSimulation GetSavedState(int Frame);

private:
	TMap<int, FSavedSimulation> SavedStates;
};
