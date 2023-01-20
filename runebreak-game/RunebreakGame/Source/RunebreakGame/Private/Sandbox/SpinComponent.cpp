// Fill out your copyright notice in the Description page of Project Settings.


#include "Sandbox/SpinComponent.h"

// Sets default values for this component's properties
USpinComponent::USpinComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float Degrees = DegreesPerSec * DeltaTime;

	FRotator Rotator = FRotator(0, Degrees, 0);
	FQuat QuatRotation = FQuat(Rotator);

	// need to communicate to parent
	GetOwner()->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

