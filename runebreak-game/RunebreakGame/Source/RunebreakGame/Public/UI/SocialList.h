// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <RunebreakGame/Public/RBGameSession/Types/CharacterClass.h>
#include "SocialList.generated.h"

UENUM(BlueprintType)
enum OnlineStatus
{
	Online	UMETA(DisplayName = "Online"),
	Idle	UMETA(DisplayName = "Idle"),
	Offline	UMETA(DisplayName = "Offline"),
};

USTRUCT(BlueprintType)
struct RUNEBREAKGAME_API FSocialListEntryData {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Subtext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<OnlineStatus> Status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<CharacterClass> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldShowClass = true;
};

UCLASS(BlueprintType)
class RUNEBREAKGAME_API USocialListEntryDataContainer : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSocialListEntryData Data;
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
