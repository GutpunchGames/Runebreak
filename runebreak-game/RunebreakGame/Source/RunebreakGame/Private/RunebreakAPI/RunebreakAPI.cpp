// Fill out your copyright notice in the Description page of Project Settings.


#include "RunebreakAPI/RunebreakAPI.h"
#include <RunebreakGame/Public/RunebreakAPI/REST/Login.h>
#include <RunebreakGame/Public/RunebreakAPI/State/StateManager.h>
#include <RunebreakGame/Public/RunebreakAPI/RBSocket/RBSocket.h>
#include <RunebreakGame/Public/RunebreakAPI/REST/Lobbies.h>

URunebreakAPI::URunebreakAPI() {
	UE_LOG(LogTemp, Warning, TEXT("Created Runebreak API"))
	stateManager = new StateManager();
	stateManager->OnStateChanged = [this](FRBState state) {
		NotifyListeners(state);
		UE_LOG(LogTemp, Warning, TEXT("got new state. token: %s -- connection state: %d"), *state.authToken, state.connectionStatus)
	};
}

void URunebreakAPI::Login(FString username, FString userId, UObject* resultHandler) {
	ULoginTransaction* loginTransaction = NewObject<ULoginTransaction>(this);

	loginTransaction->OnSuccess = [this, resultHandler](FLoginResponseBody resp) {
		HandleAuthenticated(resp.userId, resp.token);
		if (resultHandler) {
			ILoginResultHandler::Execute_OnLoginSuccess(resultHandler);
		}
	};

	loginTransaction->Login(username, userId);
}

void URunebreakAPI::FetchLobbies(UObject* resultHandler) {
	UFetchLobbiesTransaction* transaction = NewObject<UFetchLobbiesTransaction>(this);

	transaction->OnSuccess = [this, resultHandler](FFetchLobbiesResponseBody resp) {
		if (resultHandler) {
			IFetchLobbiesResultHandler::Execute_OnSuccess(resultHandler, resp);
		}
	};

	transaction->Execute(stateManager->GetState().authToken);
}

void URunebreakAPI::HandleAuthenticated(FString& userId, FString& token) {
	stateManager->HandleAuthenticated(token);
	ConnectToWebSocket(userId);
}

void URunebreakAPI::ConnectToWebSocket(FString& userId) {
	const FString ServerURL = FString::Printf(TEXT("ws://localhost:9000/connect/%s"), *userId);
	rbSocket = new RBSocket(ServerURL);
	rbSocket->OnStateChanged = [this](EConnectionStatus connectionStatus) {
		HandleSocketConnectionStatusChanged(connectionStatus);
	};
	rbSocket->OnChatMessageReceived = [this](FChatMessage* message) {
		stateManager->HandleMessageReceived(*message);
	};
	rbSocket->Connect();
}

void URunebreakAPI::HandleSocketConnectionStatusChanged(EConnectionStatus& status) {
	stateManager->HandleSocketConnectionStatusChanged(status);
}

void URunebreakAPI::AddListener(UObject* listener) {
	listeners.Add(listener);
}

void URunebreakAPI::NotifyListeners(FRBState state) {
	for (auto& listener : listeners) {
		IRBObserver::Execute_OnStateChanged(listener, state);
	}
}
