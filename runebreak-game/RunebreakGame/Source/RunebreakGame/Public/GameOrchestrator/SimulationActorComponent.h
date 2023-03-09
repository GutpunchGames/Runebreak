// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameOrchestrator/RBGameSimulation.h"
#include "SimulationActorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUNEBREAKGAME_API USimulationActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimulationActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//virtual void Sync(FRBGameSimulation Simulation);

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Simulation Actor")
	//void SimulationTick(FRBGameSimulation Simulation);
	//virtual void SimulationTick_Implementation(FRBGameSimulation Simulation);

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//FString SimulationEntityId;
};
