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

void StateManager::HandleLobbyCreate(FLobby Lobby) {
	state.currentLobby = Lobby;
	PublishState();
}

void StateManager::HandleLobbyJoin(FLobby Lobby) {
	state.currentLobby = Lobby;
	PublishState();
}

void StateManager::HandleLobbyUpdate(FLobby Lobby) {
	state.currentLobby = Lobby;
	PublishState();
}

void StateManager::HandleLobbyLeave(FString LobbyId) {
	if (state.currentLobby.lobbyId.Equals(LobbyId)) {
		state.currentLobby.Invalidate();
		PublishState();
	}
}

void StateManager::PublishState() {
	OnStateChanged(state);
}
