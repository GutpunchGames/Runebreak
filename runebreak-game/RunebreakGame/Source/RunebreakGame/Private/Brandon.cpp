// Fill out your copyright notice in the Description page of Project Settings.


#include "Brandon.h"

// Sets default values
ABrandon::ABrandon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	tickValue = 0;

}

// Called when the game starts or when spawned
void ABrandon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrandon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	tickValue = tickValue + DeltaTime;
	MaybeSayHi();
}

void ABrandon::MaybeSayHi()
{
	if (tickValue > 5) {
		UE_LOG(LogTemp, Warning, TEXT("Hi i'm brandon: %s"), *name);
		tickValue = 0;
	}
}
