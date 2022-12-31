// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include "RunebreakAPI/RBSocket/RBSocket.h"
#include "RunebreakAPI/State/StateManager.h"
#include "RunebreakAPI.generated.h"

class RBListener
{

public:
	RBListener() {}
	virtual ~RBListener() {}
	virtual void OnStateChange(RBState state) {};
};

class RBListenerImpl : public RBListener
{

public:
	RBListenerImpl() {}
	~RBListenerImpl() {}

	FString subscriberName = "testSubscriber";

	void OnStateChange(RBState state) {
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
	TSet<RBListener*> listeners;

public:
	URunebreakAPI();

	UFUNCTION(BlueprintCallable)
	void Login();

	void AddListener(RBListener* listener);

private:
	void HandleAuthenticated(FString& userId, FString& token);
	void HandleSocketConnectionStatusChanged(EConnectionStatus& status);
	void ConnectToWebSocket(FString& userId);

	void NotifyListeners(RBState state);
};
