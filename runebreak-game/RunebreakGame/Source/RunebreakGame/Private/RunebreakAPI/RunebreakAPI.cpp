// Fill out your copyright notice in the Description page of Project Settings.


#include "RunebreakAPI/RunebreakAPI.h"
#include "HTTP.h"
#include "WebSocketsModule.h" // Module definition
#include "IWebSocket.h"
#include <string>
#include "RunebreakAPI/Models/APIState.h"
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>
#include <RunebreakGame/Public/RunebreakAPI/REST/LoginRequestBody.h>
#include <RunebreakGame/Public/RunebreakAPI/REST/LoginResponseBody.h>
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>


URunebreakAPI::URunebreakAPI() {
	UE_LOG(LogTemp, Warning, TEXT("Created Runebreak API"));
}

void URunebreakAPI::Login() {
	FLoginRequestBody body = FLoginRequestBody("andy1", "password");
	FJsonObject requestJsonObject = ToJsonObject(body);
	TSharedRef<FJsonObject> test = MakeShareable(&requestJsonObject);

	FString serializedRequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&serializedRequestBody);
	FJsonSerializer::Serialize(test, Writer);

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URunebreakAPI::OnLoginResponseReceived);
	Request->SetURL("http://localhost:9000/login");
	Request->SetContentAsString(serializedRequestBody);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

void URunebreakAPI::OnLoginResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	FString respJson = *Response->GetContentAsString();
	FLoginResponseBody resp;
	FromJson(respJson, &resp);
	UE_LOG(LogTemp, Warning, TEXT("response received: %s"), *resp.ToString());
	ConnectToWebSocket(resp.userId);
}

//ws://localhost:9000/connect/${userId}

void URunebreakAPI::ConnectToWebSocket(FString& userId) {
	const FString ServerURL = FString::Printf(TEXT("ws://localhost:9000/connect/%s"), *userId);
	const FString ServerProtocol = TEXT("ws");              // The WebServer protocol you want to use.

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
		// This code will run when we receivea raw (binary) message from the server.
		// leave this commented out for now...
		});

	Socket->OnMessageSent().AddLambda([](const FString& MessageString) -> void {
		UE_LOG(LogTemp, Warning, TEXT("OnMessageSent()"))
		// This code is called after we sent a message to the server.
		});

	// And we finally connect to the server. 
	Socket->Connect();
}

