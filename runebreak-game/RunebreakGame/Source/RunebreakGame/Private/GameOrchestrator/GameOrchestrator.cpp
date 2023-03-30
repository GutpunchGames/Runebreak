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
    for (int i = 0; i < 8; i++) {
        FVector Origin;
        FRotator Rotator;
		ADetectionBoxActor* DetectionBoxActor = Cast<ADetectionBoxActor>(GetWorld()->SpawnActor(DetectionBoxActorPrototype, &Origin, &Rotator));
        DetectionBoxActor->MarkInactive();
        DetectionBoxActors.Add(DetectionBoxActor);
    }
}

void AGameOrchestrator::OnSessionStarted_Implementation() {
}

void AGameOrchestrator::ActorSync() {
    // update existence. todo: only loop over entities marked for existence-syncing
    for (auto& Entry : Simulation->Entities) {
        USimulationEntity* Entity = Entry.Value;

        ASimulationActor** EntityActorMapRef = EntityActors.Find(Entity->Id);
        if (EntityActorMapRef) {
            (*EntityActorMapRef)->BindEntity(Entity);
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("Spawning actor for entity id: %d"), Entity->Id)
			FVector Position;
            Position.X = 0;
            Position.Y = 0;
            Position.Z = 0;
			FRotator Rotator;
			ASimulationActor* EntityActor = Cast<ASimulationActor>(GetWorld()->SpawnActor(Entity->ActorClass, &Position, &Rotator));
			EntityActor->BindEntity(Entity);
			EntityActors.Add(Entity->Id, EntityActor);
        }
    }

    // update actors that are staying, destroy those that are not. TODO: return them to a pool when deleted
    for (TMap<int32, ASimulationActor*>::TIterator Iterator = EntityActors.CreateIterator(); Iterator; ++Iterator)
    {
        if (Simulation->Entities.Contains(Iterator.Key())) {
			Iterator.Value()->UpdateRendering();
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("Despawning actor for entity id: %d"), Iterator.Key())
			GetWorld()->DestroyActor(Iterator.Value());
            Iterator.RemoveCurrent();
        }
    }

    for (int i = 0; i < DetectionBoxActors.Num(); i++) {
        ADetectionBoxActor* Actor = DetectionBoxActors[i];
        if (i < Simulation->NumActiveDetectionBoxes) {
            Actor->SetDetectionBox(Simulation->DetectionBoxes[i]);
        }
        else {
            Actor->MarkInactive();
        }
    }
}
