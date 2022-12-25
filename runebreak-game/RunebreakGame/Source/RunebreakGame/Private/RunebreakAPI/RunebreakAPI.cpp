// Fill out your copyright notice in the Description page of Project Settings.


#include "RunebreakAPI/RunebreakAPI.h"
#include "HTTP.h"
#include <string>
#include "RunebreakAPI/Models/APIState.h"

URunebreakAPI::URunebreakAPI() {
	UE_LOG(LogTemp, Warning, TEXT("Created Runebreak API"));
}

void URunebreakAPI::TestJsonSerialization() {
	EConnectionStatus connectionStatus = EConnectionStatus::Connecting;
	FString s = FString("hello");
	switch (connectionStatus) {
		case EConnectionStatus::Uninitialized:
			s = FString("Uninitialized");
			break;
		case EConnectionStatus::Connecting:
			s = FString("Connecting");
			break;
		case EConnectionStatus::Connected:
			s = FString("Connected");
			break;
	}
	UE_LOG(LogTemp, Warning, TEXT("Test Method Called. Connection Status: %s"), *s);
}

void URunebreakAPI::DoThing() {
	UE_LOG(LogTemp, Warning, TEXT("DoThing called in Runebreak API"));
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &URunebreakAPI::OnResponseReceived);
	Request->SetURL("https://jsonplaceholder.typicode.com/posts/1");
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void URunebreakAPI::Login() {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", "andy1");
	RequestObj->SetStringField("password", "password");

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &URunebreakAPI::OnResponseReceived);
	Request->SetURL("http://localhost:9000/login");
	Request->SetContentAsString(RequestBody);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

void URunebreakAPI::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	UE_LOG(LogTemp, Warning, TEXT("response received: %s"), *Response->GetContentAsString());
}
