// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/PlayerSpawnPoint.h"

APlayerSpawnPoint::APlayerSpawnPoint() {
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
}

void APlayerSpawnPoint::BeginPlay() {
	Super::BeginPlay();
}
