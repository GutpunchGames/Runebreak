// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include "RunebreakAPI/RBSocket/RBSocket.h"
#include "RunebreakAPI/State/StateManager.h"
#include "RunebreakAPI.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class URBListenerBP : public UInterface
{
	GENERATED_BODY()
};

class IRBListenerBP
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnStateChange(FRBState state);

	void OnStateChange_Implementation(FRBState state) {
		UE_LOG(LogTemp, Warning, TEXT("OnStateChange: %d"), state.connectionStatus)
	}
};

UCLASS()
class RUNEBREAKGAME_API URunebreakAPI : public UObject
{
	GENERATED_BODY()

private:
	RBSocket* rbSocket;
	StateManager* stateManager;
	TSet<IRBListenerBP*> listeners;

public:
	URunebreakAPI();

	UFUNCTION(BlueprintCallable)
	void Login();

	void AddListener(IRBListenerBP* listener);

private:
	void HandleAuthenticated(FString& userId, FString& token);
	void HandleSocketConnectionStatusChanged(EConnectionStatus& status);
	void ConnectToWebSocket(FString& userId);

	void NotifyListeners(FRBState state);
};
