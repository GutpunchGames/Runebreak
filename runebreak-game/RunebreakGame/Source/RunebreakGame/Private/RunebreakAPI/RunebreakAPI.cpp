// Fill out your copyright notice in the Description page of Project Settings.


#include "RunebreakAPI/RunebreakAPI.h"
#include "HTTP.h"
#include <string>
#include "RunebreakAPI/Models/APIState.h"
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>
#include <RunebreakGame/Public/RunebreakAPI/REST/LoginRequestBody.h>

URunebreakAPI::URunebreakAPI() {
	UE_LOG(LogTemp, Warning, TEXT("Created Runebreak API"));
}

void URunebreakAPI::TestJsonSerialization() {
	URunebreakAPI::Login();
}

void URunebreakAPI::Login() {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	FLoginRequestBody body;
	body.username = "andy1";
	body.password = "password";
	FJsonObject requestJsonObject = FLoginRequestBody::ToJsonObject(body);

	TSharedRef<FJsonObject> test = MakeShareable(&requestJsonObject);
	
	FString serializedRequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&serializedRequestBody);
	FJsonSerializer::Serialize(test, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &URunebreakAPI::OnResponseReceived);
	Request->SetURL("http://localhost:9000/login");
	Request->SetContentAsString(serializedRequestBody);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

void URunebreakAPI::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	UE_LOG(LogTemp, Warning, TEXT("response received: %s"), *Response->GetContentAsString());
}
