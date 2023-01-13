// Fill out your copyright notice in the Description page of Project Settings.


#include "RBGameSession/RBGameSession.h"
#include <RunebreakGame/Public/RBGameSession/REST/Login.h>
#include <RunebreakGame/Public/RBGameSession/State/StateManager.h>
#include <RunebreakGame/Public/RBGameSession/RBSocket/RBSocket.h>
#include <RunebreakGame/Public/RBGameSession/REST/Lobbies.h>

URBGameSession::URBGameSession() {
	stateManager = new StateManager();
	stateManager->OnStateChanged = [this](FRBState state) {
		NotifyListeners(state);
	};
}

void URBGameSession::Login(FString username, FString userId, FCallback OnSuccess, FCallback OnFailure) {
	FHttpRequestRef loginRequest = DoLoginRESTCall(username, userId, [this, OnSuccess](FLoginResponseBody resp) {
		HandleAuthenticated(resp.userId, resp.token);
		OnSuccess.ExecuteIfBound();
	}, [this, OnFailure]() {
		OnFailure.ExecuteIfBound();
	});
}

void URBGameSession::FetchLobbies(FOnLobbiesFetched OnSuccess, FCallback OnFailure) {
	FHttpRequestRef request = GetLobbiesRESTCall([OnSuccess, this](FFetchLobbiesResponseBody resp) {
		OnSuccess.ExecuteIfBound(resp);
	}, [this, OnFailure]() {
		OnFailure.ExecuteIfBound();
	});
	AddAuthHeaders(request);
	request->ProcessRequest();
}

void URBGameSession::HandleAuthenticated(FString& userId, FString& token) {
	stateManager->HandleAuthenticated(token);
	ConnectToWebSocket(userId);
}

void URBGameSession::ConnectToWebSocket(FString& userId) {
	const FString ServerURL = FString::Printf(TEXT("ws://localhost:9000/connect/%s"), *userId);
	rbSocket = new RBSocket(ServerURL);
	rbSocket->ConnectionStatusChangedEvent.AddLambda([this](EConnectionStatus connectionStatus) {
		HandleSocketConnectionStatusChanged(connectionStatus);
	});
	rbSocket->ChatMessageReceivedEvent.AddLambda([this](FChatMessage message) {
		stateManager->HandleMessageReceived(message);
	});
	rbSocket->Connect();
}

void URBGameSession::HandleSocketConnectionStatusChanged(EConnectionStatus& status) {
	stateManager->HandleSocketConnectionStatusChanged(status);
}

void URBGameSession::NotifyListeners(FRBState state) {
	OnGameSessionStateChanged.Broadcast(state);
}

void URBGameSession::AddAuthHeaders(FHttpRequestRef HttpRequestRef) {
	HttpRequestRef->SetHeader("X-Auth-Token", stateManager->GetState().authToken);
}
