// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameOrchestrator.h"

// Sets default values
AGameOrchestrator::AGameOrchestrator()
{
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

FTransform AGameOrchestrator::GetPlayerTransform(int32 PlayerIndex) {
	return FTransform();
}
