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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Init() override;

	void OnSessionStarted_Implementation();

	void TickGameState();

	void RunFrame();

	void GetLocalInputs();

	FTransform GetPlayerTransform(int32 PlayerIndex);

	int32 Inputs[2] = { 0, 0 };
};
