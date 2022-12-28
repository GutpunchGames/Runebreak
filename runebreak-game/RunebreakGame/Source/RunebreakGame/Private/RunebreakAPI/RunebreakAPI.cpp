// Fill out your copyright notice in the Description page of Project Settings.


#include "RunebreakAPI/RunebreakAPI.h"
#include "HTTP.h"
#include <string>
#include "RunebreakAPI/Models/APIState.h"
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>
#include <RunebreakGame/Public/RunebreakAPI/REST/Login.h>
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>
#include <Runtime/Online/WebSockets/Public/WebSocketsModule.h>
#include <Runtime/Online/WebSockets/Public/IWebSocket.h>

URunebreakAPI::URunebreakAPI() {
	UE_LOG(LogTemp, Warning, TEXT("Created Runebreak API"));
}

void URunebreakAPI::Login() {
	ULoginTransaction* loginTransaction = NewObject<ULoginTransaction>(this);

	loginTransaction->OnSuccess =  [this](FLoginResponseBody resp) {
			UE_LOG(LogTemp, Warning, TEXT("%s"), *resp.ToString())
			// todo: connect to websocket
			ConnectToWebSocket(resp.userId);
	};

	loginTransaction->Login();
}

void URunebreakAPI::ConnectToWebSocket(FString& userId) {
	const FString ServerURL = FString::Printf(TEXT("ws://localhost:9000/connect/%s"), *userId);
	const FString ServerProtocol = TEXT("ws");
	UE_LOG(LogTemp, Warning, TEXT("server URL: %s"), *ServerURL)

	TSharedPtr<IWebSocket> Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);

	// We bind all available events
	Socket->OnConnected().AddLambda([]() -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnConnected()"))
			// This code will run once connected.
		});

	Socket->OnConnectionError().AddLambda([](const FString& Error) -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnConnectionError()"))
			// This code will run if the connection failed. Check Error to see what happened.
		});

	Socket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnClosed()"))
			// This code will run when the connection to the server has been terminated.
			// Because of an error or a call to Socket->Close().
		});

	Socket->OnMessage().AddLambda([](const FString& Message) -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnMessage(%s)"), *Message);
		// This code will run when we receive a string message from the server.
		});

	Socket->OnRawMessage().AddLambda([](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) -> void {
		//UE_LOG(LogTemp, Warning, TEXT("OnRawMessage()"))
		// This code will run when we receive a raw (binary) message from the server.
		// leave this commented out for now...
		});

	Socket->OnMessageSent().AddLambda([](const FString& MessageString) -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnMessageSent()"))
			// This code is called after we sent a message to the server.
		});

	// And we finally connect to the server. 
	Socket->Connect();
}
