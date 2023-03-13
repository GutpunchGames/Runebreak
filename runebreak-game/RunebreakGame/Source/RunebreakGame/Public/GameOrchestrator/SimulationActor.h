// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOrchestrator/RBSimulationEntity.h"
#include "GameOrchestrator/RBGamePrimitives.h"
#include "SimulationActor.generated.h"

UCLASS()
class RUNEBREAKGAME_API ASimulationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BindEntity(USimulationEntity* _Entity);
	virtual void UnbindEntity();

	UFUNCTION(BlueprintNativeEvent, Category = "Simulation Actor")
	void UpdateRendering();
	virtual void UpdateRendering_Implementation();

protected:
	UPROPERTY(BlueprintReadOnly)
	USimulationEntity* Entity;
};
