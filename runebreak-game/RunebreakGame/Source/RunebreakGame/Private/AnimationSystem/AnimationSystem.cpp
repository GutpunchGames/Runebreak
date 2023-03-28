// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationSystem/AnimationSystem.h"

void URBEntityAnimator::SetAnimationForState(FString StateName, const int32& Frame) {
	UE_LOG(LogTemp, Warning, TEXT("Setting animation for state: %s -- %d"), *StateName, Frame)
}
