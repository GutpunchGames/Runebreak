// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <RunebreakGame/Public/GameOrchestrator/InputBuffer.h>
#include "SimulationActor.generated.h"

UCLASS()
class RUNEBREAKGAME_API ASimulationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulationActor();

	UPROPERTY()
	FString SimulationId;

	UPROPERTY()
	FVector SimulationLocation;

	UPROPERTY()
	int ActorId;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void SimulationTick(int Frame, IInputBuffer* Player1InputBuffer, IInputBuffer* Player2InputBuffer);
	virtual FString SerializeState();
	virtual void Deserialize(const FString& Bytes);
};
