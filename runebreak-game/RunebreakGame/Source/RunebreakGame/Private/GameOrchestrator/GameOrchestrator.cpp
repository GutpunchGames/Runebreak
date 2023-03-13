// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameOrchestrator.h"

// Sets default values
AGameOrchestrator::AGameOrchestrator()
{
    Simulation = CreateDefaultSubobject<URBGameSimulation>(TEXT("GameSimulation"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void AGameOrchestrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameOrchestrator::Init()
{
}

void AGameOrchestrator::OnSessionStarted_Implementation() {
}

void AGameOrchestrator::ActorSync() {
    // update existence. todo: only loop over entities marked for existence-syncing
    for (auto& Entry : Simulation->EntityIndex) {
        USimulationEntity* Entity = Entry.Value;
        if (!EntityActors.Contains(Entity->Id)) {
			FVector Position;
			FRotator Rotator;
            ASimulationActor* Actor = Cast<ASimulationActor>(GetWorld()->SpawnActor(Entity->ActorClass, &Position, &Rotator));
            UE_LOG(LogTemp, Warning, TEXT("Spawned actor"))
            Actor->BindEntity(Entity);
            EntityActors.Add(Entity->Id, Actor);
        }
    }

    // todo: delete unneeded actors, return them to a pool

    // update rendering
    for (auto& Entry : Simulation->EntityIndex) {
        USimulationEntity* Entity = Entry.Value;
		EntityActors[Entity->Id]->UpdateRendering();
    }
}
