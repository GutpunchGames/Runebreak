// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOrchestrator/RBGameSimulation.h"
#include "GameOrchestrator/RBNonGameState.h"
#include "GameOrchestrator.generated.h"

UCLASS()
class RUNEBREAKGAME_API AGameOrchestrator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameOrchestrator();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Init();

	/**
	 * Called from BeginPlay() after creating the game state.
	 * Can be overridden by a blueprint to create actors that represent the game state.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GameOrchestrator")
	void OnSessionStarted();
	virtual void OnSessionStarted_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FTransform GetPlayerTransform(int PlayerId);

	FRBGameSimulation Simulation;
	NonGameState ngs = { 0 };

	float ElapsedTime = 0;;
};
