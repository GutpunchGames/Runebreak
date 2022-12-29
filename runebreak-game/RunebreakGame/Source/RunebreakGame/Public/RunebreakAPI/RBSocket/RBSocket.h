// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RunebreakGame/Public/RunebreakAPI/Models/ChatMessage.h>
#include <RunebreakGame/Public/RunebreakAPI/Models/ConnectionStatus.h>

/**
 * 
 */
class RUNEBREAKGAME_API RBSocket
{

private:
	FString url;
	EConnectionStatus connectionStatus = EConnectionStatus::Uninitialized;

public:
	RBSocket(const FString& _url);
	~RBSocket();

	TFunction<void(EConnectionStatus)> OnStateChanged;
	TFunction<void(FChatMessage*)> OnChatMessageReceived;

	void Connect();
};
