// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SocialList.generated.h"

UCLASS(BlueprintType)
class RUNEBREAKGAME_API USocialListEntryData : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString TextValue;
};

/**
 * 
 */
UCLASS()
class RUNEBREAKGAME_API USocialList : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetSocialItems();

protected:
	virtual void NativeConstruct() override;
};
