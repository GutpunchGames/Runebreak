// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOrchestrator/RBGameState.h"
#include "GameOrchestrator/RBNonGameState.h"
#include "GameOrchestrator.generated.h"

UCLASS()
class RUNEBREAKGAME_API AGameOrchestrator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameOrchestrator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Called from BeginPlay() after creating the game state.
	 * Can be overridden by a blueprint to create actors that represent the game state.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GameOrchestrator")
	void OnSessionStarted();
	virtual void OnSessionStarted_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FTransform GetPlayerTransform(int32 PlayerIndex);

	GameState gs = { 0 };
	NonGameState ngs = { 0 };
};
