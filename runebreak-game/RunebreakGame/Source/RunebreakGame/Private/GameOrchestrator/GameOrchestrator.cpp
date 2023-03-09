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
    URBPlayer* Player = Simulation->GetPlayer(PlayerId);
    FVector Position = FVector(0, (float)Player->State.Position.x, (float)Player->State.Position.y);
    FQuat Rotation = FRotator(0, 0, 0).Quaternion();
    FTransform Result = FTransform(Rotation, Position);
    return Result;
}
