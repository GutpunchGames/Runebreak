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

FTransform AGameOrchestrator::GetPlayerTransform(int PlayerId) {
    FRBPlayer* Player = Simulation->GetPlayer(PlayerId);
    FVector Position = FVector(0, (float)Player->position.x, (float)Player->position.y);
    FQuat Rotation = FRotator(0, 0, 0).Quaternion();
    FTransform Result = FTransform(Rotation, Position);
    return Result;
}
