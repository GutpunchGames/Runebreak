// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include "RunebreakAPI/RBSocket/RBSocket.h"
#include "RunebreakAPI/State/StateManager.h"
#include "RunebreakAPI.generated.h"

UCLASS()
class RUNEBREAKGAME_API URunebreakAPI : public UObject
{
	GENERATED_BODY()

private:
	RBSocket* rbSocket;
	StateManager* stateManager;

public:
	URunebreakAPI();

	UFUNCTION(BlueprintCallable)
	void Login();

private:
	void HandleAuthenticated(FString& userId, FString& token);
	void HandleSocketConnectionStatusChanged(EConnectionStatus& status);
	void ConnectToWebSocket(FString& userId);
};
