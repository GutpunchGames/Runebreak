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

FRBState URBGameSession::GetCurrentState() {
	return stateManager->GetState();
}

void URBGameSession::Login(FString username, FString password, FCallback OnSuccess, FCallback OnFailure) {
	FHttpRequestRef loginRequest = DoLoginRESTCall(username, password,
		[this, username, OnSuccess](FLoginResponseBody resp) {
			HandleAuthenticated(resp.userId, username, resp.token);
			OnSuccess.ExecuteIfBound();
		},
		[this, OnFailure]() {
			OnFailure.ExecuteIfBound();
		});
}

void URBGameSession::Register(FString username, FString password, FCallback OnSuccess, FCallback OnFailure) {
	FHttpRequestRef registerRequest = DoRegisterRESTCall(username, password,
		[this, username, OnSuccess](FLoginResponseBody resp) {
			HandleAuthenticated(resp.userId, username, resp.token);
			OnSuccess.ExecuteIfBound();
		},
		[this, OnFailure]() {
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

void URBGameSession::CreateLobby(FString LobbyName, FOnCreatedOrJoinedLobby OnSuccess, FCallback OnFailure) {
	FHttpRequestRef request = CreateLobbyRESTCall(LobbyName,
		[this, OnSuccess](FLobby resp) {
			stateManager->HandleLobbyCreate(resp);
			OnSuccess.ExecuteIfBound(resp);
		},
		[this, OnFailure]() {
			OnFailure.ExecuteIfBound();
		});
	AddAuthHeaders(request);
	request->ProcessRequest();
}

void URBGameSession::JoinLobby(FString LobbyId, FOnCreatedOrJoinedLobby OnSuccess, FCallback OnFailure) {
	FHttpRequestRef request = JoinLobbyRESTCall(LobbyId,
		[this, OnSuccess](FLobby resp) {
			stateManager->HandleLobbyJoin(resp);
			OnSuccess.ExecuteIfBound(resp);
		},
		[this, OnFailure]() {
			OnFailure.ExecuteIfBound();
		});
	AddAuthHeaders(request);
	request->ProcessRequest();
}

void URBGameSession::LeaveLobby(FString LobbyId, FCallback OnSuccess, FCallback OnFailure) {
	FHttpRequestRef request = LeaveLobbyRESTCall(LobbyId,
		[this, LobbyId, OnSuccess]() {
			stateManager->HandleLobbyLeave(LobbyId);
			OnSuccess.ExecuteIfBound();
		},
		[this, OnFailure]() {
			OnFailure.ExecuteIfBound();
		});
	AddAuthHeaders(request);
	request->ProcessRequest();
}

void URBGameSession::HandleAuthenticated(FString& userId, const FString username, FString& token) {
	FUser user;
	user.userId = userId;
	user.username = username;
	stateManager->HandleAuthenticated(token, user);
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
	rbSocket->LobbyUpdatedEvent.AddLambda([this](FLobby lobby) {
		stateManager->HandleLobbyUpdate(lobby);
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
