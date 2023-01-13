// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RunebreakGame/Public/RBGameSession/Models/ChatMessage.h>
#include <RunebreakGame/Public/RBGameSession/Models/ConnectionStatus.h>

DECLARE_EVENT_OneParam(URBSocket, FConnectionStatusChangedEvent, EConnectionStatus)
DECLARE_EVENT_OneParam(URBSocket, FChatMessageReceivedEvent, FChatMessage)

// todo: add other events
//DECLARE_EVENT_OneParam(URBSocket, FLobbyUpdate, FLobby)

class RUNEBREAKGAME_API RBSocket
{

private:
	FString url;
	EConnectionStatus connectionStatus = EConnectionStatus::Uninitialized;

public:
	RBSocket(const FString& _url);
	~RBSocket();

	FConnectionStatusChangedEvent ConnectionStatusChangedEvent;
	FChatMessageReceivedEvent ChatMessageReceivedEvent;

	void Connect();
};
