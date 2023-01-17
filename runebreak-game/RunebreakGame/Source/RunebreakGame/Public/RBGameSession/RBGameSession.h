// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include "RBGameSession/REST/Lobbies.h"
#include "RBGameSession/RBSocket/RBSocket.h"
#include "RBGameSession/State/StateManager.h"
#include "RBGameSession.generated.h"

// todo: move these declarations
DECLARE_DYNAMIC_DELEGATE(FCallback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSessionStateChangedEvent, FRBState, State);

UCLASS()
class RUNEBREAKGAME_API URBGameSession : public UObject
{
	GENERATED_BODY()

private:
	RBSocket* rbSocket;
	StateManager* stateManager;

public:
	URBGameSession();

	UFUNCTION(BlueprintCallable)
	void Login(FString username, FString userId, FCallback OnSuccess, FCallback OnFailure);

	UFUNCTION(BlueprintCallable)
	void FetchLobbies(FOnLobbiesFetched OnSuccess, FCallback OnFailure);

	UFUNCTION(BlueprintCallable)
	void CreateLobby(FString LobbyName, FOnCreatedOrJoinedLobby OnSuccess, FCallback OnFailure);

	UFUNCTION(BlueprintCallable)
	void JoinLobby(FString LobbyId, FOnCreatedOrJoinedLobby OnSuccess, FCallback OnFailure);

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FOnGameSessionStateChangedEvent OnGameSessionStateChanged;

	UFUNCTION(BlueprintCallable)
	FRBState GetCurrentState();

private:
	void HandleAuthenticated(FString& userId, FString& token);
	void HandleSocketConnectionStatusChanged(EConnectionStatus& status);
	void ConnectToWebSocket(FString& userId);

	void NotifyListeners(FRBState state);

	void AddAuthHeaders(FHttpRequestRef HttpRequestRef);
};
