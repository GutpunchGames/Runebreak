// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/InputComponent.h"
#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include "PlayerInputProcessor.generated.h"

/**
 * 
 */
UCLASS()
class RUNEBREAKGAME_API UPlayerInputProcessor : public UObject
{
	GENERATED_BODY()

public:
	UPlayerInputProcessor();
	void Bind(int PlayerIndex, UInputComponent* InputComponent);

	FInput Input;

	void HandleMoveUpPressed();
	void HandleMoveUpReleased();
	void HandleMoveDownPressed();
	void HandleMoveDownReleased();
};
