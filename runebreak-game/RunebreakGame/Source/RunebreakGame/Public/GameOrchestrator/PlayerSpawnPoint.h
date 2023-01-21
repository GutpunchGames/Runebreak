// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameOrchestrator/PlayerSpawnConfig.h"
#include "PlayerSpawnPoint.generated.h"

UCLASS(Blueprintable)
class RUNEBREAKGAME_API APlayerSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerSpawnPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPlayerSpawnConfig PlayerSpawnConfig;

protected:
	virtual void BeginPlay() override;
};
