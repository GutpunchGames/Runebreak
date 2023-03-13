// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/SimulationActor.h"

// Sets default values
ASimulationActor::ASimulationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimulationActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimulationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimulationActor::BindEntity(USimulationEntity* _Entity) {
	Entity = _Entity;
}

void ASimulationActor::UnbindEntity() {
	Entity = 0;
}

void ASimulationActor::UpdateRendering_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("UpdateRendering_Implementation)"))
}
