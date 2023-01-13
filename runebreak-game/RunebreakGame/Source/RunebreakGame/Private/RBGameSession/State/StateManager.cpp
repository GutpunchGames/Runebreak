// Fill out your copyright notice in the Description page of Project Settings.


#include "RBGameSession/State/StateManager.h"

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

FRBState StateManager::GetState() {
	return state;
}

void StateManager::HandleAuthenticated(FString token) {
	state.authToken = token;
	PublishState();
}

void StateManager::HandleSocketConnectionStatusChanged(EConnectionStatus status) {
	state.connectionStatus = status;
	PublishState();
}

void StateManager::HandleMessageReceived(FChatMessage message) {
	state.mostRecentMessage = message;
	PublishState();
}

void StateManager::PublishState() {
	OnStateChanged(state);
}
