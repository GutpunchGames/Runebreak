// Fill out your copyright notice in the Description page of Project Settings.


#include "RBGameSession/RBSocket/RBSocket.h"

#include "HTTP.h"
#include "Misc/Base64.h"
#include <Runtime/Online/WebSockets/Public/WebSocketsModule.h>
#include <Runtime/Online/WebSockets/Public/IWebSocket.h>
#include <RunebreakGame/Public/RBGameSession/Utilities/JsonUtils.h>
#include <RunebreakGame/Public/RBGameSession/Models/ChatMessage.h>

RBSocket::RBSocket(const FString& _url)
{
	url = _url;
}

RBSocket::~RBSocket()
{
}

void RBSocket::Connect() {
	const FString ServerProtocol = TEXT("ws");

	TSharedPtr<IWebSocket> Socket = FWebSocketsModule::Get().CreateWebSocket(url, ServerProtocol);

	ConnectionStatusChangedEvent.Broadcast(EConnectionStatus::Connecting);

	// We bind all available events
	Socket->OnConnected().AddLambda([this]() -> void {
		ConnectionStatusChangedEvent.Broadcast(EConnectionStatus::Connected);
	});

	Socket->OnConnectionError().AddLambda([this](const FString& Error) -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnConnectionError()"))
			// This code will run if the connection failed. Check Error to see what happened.
	});

	Socket->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean) -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnClosed()"))
			// This code will run when the connection to the server has been terminated.
			// Because of an error or a call to Socket->Close().
	});

	Socket->OnMessage().AddLambda([this](const FString& Message) -> void {
		FSocketMessage* message = new FSocketMessage();
		FromJson(Message, message);
		if (message->MessageType.Equals("LOBBY_UPDATE")) {
			FString decoded = Base64Decode(message->Payload);
			UE_LOG(LogTemp, Warning, TEXT("got decoded message: %s"), *decoded);
			FLobby* lobby = new FLobby();
			FromJson(decoded, lobby);
			FUser user = lobby->users[0];
			UE_LOG(LogTemp, Warning, TEXT("lobby had user (c++): %s"), *user.ToString());
			LobbyUpdatedEvent.Broadcast(*lobby);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("unhandled message of type: %s"), *message->MessageType)
		}
	});

	Socket->OnRawMessage().AddLambda([this](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) -> void {
		//UE_LOG(LogTemp, Warning, TEXT("OnRawMessage()"))
		// This code will run when we receive a raw (binary) message from the server.
		// leave this commented out for now...
	});

	Socket->OnMessageSent().AddLambda([this](const FString& MessageString) -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnMessageSent()"))
			// This code is called after we sent a message to the server.
	});

	// And we finally connect to the server. 
	Socket->Connect();
}

FString RBSocket::Base64Decode(FString src) {
	FString Dest;
	TArray<uint8> ByteArray;
	bool Success = FBase64::Decode(src, Dest);
	return Dest;
}
