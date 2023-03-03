// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/GameOrchestrator.h"
#include "LocalGameOrchestrator.generated.h"

UCLASS()
class RUNEBREAKGAME_API ALocalGameOrchestrator : public AGameOrchestrator
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocalGameOrchestrator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
