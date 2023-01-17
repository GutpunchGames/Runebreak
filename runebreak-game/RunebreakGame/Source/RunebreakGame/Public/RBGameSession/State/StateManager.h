// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <RunebreakGame/Public/RBGameSession/Types/LobbyTypes.h>
#include <RunebreakGame/Public/RBGameSession/Models/ChatMessage.h>
#include <RunebreakGame/Public/RBGameSession/Models/ConnectionStatus.h>
#include "StateManager.generated.h"

USTRUCT(BlueprintType)
struct FRBState {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Authentication")
		FString authToken = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EConnectionStatus connectionStatus = EConnectionStatus::Uninitialized;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FChatMessage mostRecentMessage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FLobby currentLobby;
};

class StateManager
{

public:
	StateManager();
	~StateManager();

	TFunction<void(FRBState)> OnStateChanged;

	// all the methods for handling updates
	void HandleAuthenticated(FString token);
	void HandleSocketConnectionStatusChanged(EConnectionStatus status);
	void HandleMessageReceived(FChatMessage message);

	void HandleLobbyCreate(FLobby Lobby);
	void HandleLobbyJoin(FLobby Lobby);
	void HandleLobbyUpdate(FLobby Lobby);
	void HandleLobbyLeave(FString LobbyId);

	FRBState GetState();

private:
	FRBState state;
	void PublishState();
};
