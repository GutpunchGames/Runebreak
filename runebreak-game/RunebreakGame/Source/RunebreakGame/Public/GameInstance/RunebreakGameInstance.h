// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GGPOGameInstance.h"
#include <RunebreakGame/Public/RBGameSession/RBGameSession.h>
#include "RunebreakGameInstance.generated.h"

UCLASS()
class RUNEBREAKGAME_API URunebreakGameInstance : public UGGPOGameInstance
{
	GENERATED_BODY()

public:
	URunebreakGameInstance();

	UPROPERTY(BlueprintReadOnly)
	URBGameSession* gameSession;
};