// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include "RunebreakAPI/RBSocket/RBSocket.h"
#include "RunebreakAPI/State/StateManager.h"
#include "RunebreakAPI.generated.h"

UINTERFACE(Blueprintable)
class URBObserver : public UInterface
{
	GENERATED_BODY()
};

class RUNEBREAKGAME_API IRBObserver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnStateChanged(const FRBState& state);
};

UCLASS()
class RUNEBREAKGAME_API URunebreakAPI : public UObject
{
	GENERATED_BODY()

private:
	RBSocket* rbSocket;
	StateManager* stateManager;
	TSet<UObject*> listeners;

public:
	URunebreakAPI();

	UFUNCTION(BlueprintCallable)
	void Login();

	UFUNCTION(BlueprintCallable)
	void AddListener(UObject* listener);

private:
	void HandleAuthenticated(FString& userId, FString& token);
	void HandleSocketConnectionStatusChanged(EConnectionStatus& status);
	void ConnectToWebSocket(FString& userId);

	void NotifyListeners(FRBState state);
};
