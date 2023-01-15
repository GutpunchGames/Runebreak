// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brandon.generated.h"

UCLASS()
class RUNEBREAKGAME_API ABrandon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrandon();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString name;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float tickValue;
	virtual void MaybeSayHi();
};
