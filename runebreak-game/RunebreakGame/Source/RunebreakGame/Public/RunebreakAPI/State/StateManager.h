// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <RunebreakGame/Public/RunebreakAPI/Models/ChatMessage.h>
#include <RunebreakGame/Public/RunebreakAPI/Models/ConnectionStatus.h>

struct RBState {
	FString authToken = "";
	EConnectionStatus connectionStatus = EConnectionStatus::Uninitialized;
	int numMessagesReceived = 0;
};

class StateManager
{

public:
	StateManager();
	~StateManager();

	TFunction<void(RBState)> OnStateChanged;

	// all the methods for handling updates
	void HandleAuthenticated(FString token);
	void HandleSocketConnectionStatusChanged(EConnectionStatus status);
	void HandleMessageReceived(FChatMessage* message);

private:
	RBState state;
	void PublishState();
};
