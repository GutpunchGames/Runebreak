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
    for (auto& Entry : Simulation->Entities) {
        USimulationEntity* Entity = Entry.Value;
        ASimulationActor* EntityActor;

        ASimulationActor** EntityActorMapRef = EntityActors.Find(Entity->Id);
        if (EntityActorMapRef) {
            EntityActor = *EntityActorMapRef;
            UE_LOG(LogTemp, Warning, TEXT("Reused actor for entity id: %d"), Entity->Id)
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("Spawning actor for entity id: %d"), Entity->Id)
			FVector Position;
			FRotator Rotator;
			EntityActor = Cast<ASimulationActor>(GetWorld()->SpawnActor(Entity->ActorClass, &Position, &Rotator));
        }
		EntityActor->BindEntity(Entity);
		EntityActors.Add(Entity->Id, EntityActor);
    }

    // todo: delete unneeded actors. TODO: return them to a pool
    for (TMap<int32, ASimulationActor*>::TIterator Iterator = EntityActors.CreateIterator(); Iterator; ++Iterator)
    {
        if (!(Simulation->Entities.Contains(Iterator.Key()))) {
            Iterator.RemoveCurrent();
        }
    }

    // update rendering
    for (auto& Entry : Simulation->Entities) {
        USimulationEntity* Entity = Entry.Value;
		EntityActors[Entity->Id]->UpdateRendering();
    }
}
