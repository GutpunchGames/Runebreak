// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationSystem.generated.h"

USTRUCT(Blueprintable)
struct FRBAnimation {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString UEAnimationName;
};

UCLASS(Blueprintable)
class URBEntityAnimator : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FString, FRBAnimation> Animations;

	UFUNCTION()
	void SetAnimationForState(FString StateName, const int32& Frame);
};
