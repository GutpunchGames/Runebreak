// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SimulationActor.h"

// Sets default values
ASimulationActor::ASimulationActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASimulationActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASimulationActor::SimulationTick(int Frame, IInputBuffer* InputBuffer) {
}

FString ASimulationActor::SerializeState() {
	FVector Location = GetActorLocation();
	return "location: " + Location.ToString();
}

