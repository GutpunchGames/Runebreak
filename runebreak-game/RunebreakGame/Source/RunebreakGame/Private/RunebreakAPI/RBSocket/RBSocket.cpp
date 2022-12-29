// Fill out your copyright notice in the Description page of Project Settings.


#include "RunebreakAPI/RBSocket/RBSocket.h"

#include "HTTP.h"
#include <Runtime/Online/WebSockets/Public/WebSocketsModule.h>
#include <Runtime/Online/WebSockets/Public/IWebSocket.h>
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>
#include <RunebreakGame/Public/RunebreakAPI/Models/ChatMessage.h>

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

	OnStateChanged(EConnectionStatus::Connecting);

	// We bind all available events
	Socket->OnConnected().AddLambda([this]() -> void {
		OnStateChanged(EConnectionStatus::Connected);
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
		UE_LOG(LogTemp, Warning, TEXT("thread id on ws message: %d"), FPlatformTLS::GetCurrentThreadId())
		UE_LOG(LogTemp, Warning, TEXT("OnMessage(%s)"), *Message);
		FChatMessage* msg = new FChatMessage();
		FromJson(Message, msg);
		UE_LOG(LogTemp, Warning, TEXT("deserialized message successfully : %s"), *msg->ToString());
		OnChatMessageReceived(msg);
		// This code will run when we receive a string message from the server.
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
