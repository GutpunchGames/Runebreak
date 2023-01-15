// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <RunebreakGame/Public/RBGameSession/RBGameSession.h>
#include "RunebreakGameInstance.generated.h"

UCLASS()
class RUNEBREAKGAME_API URunebreakGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URunebreakGameInstance();

	UPROPERTY(BlueprintReadOnly)
	URBGameSession* gameSession;

	// this attempts to fix a bug, detailed here: 
	// https://forums.unrealengine.com/t/pig-of-a-crash-pure-virtual-function-being-called-while-application-was-running/155116/13
	virtual void Init() override {};
	virtual void Shutdown() override {};
	virtual void StartGameInstance() override {};
};