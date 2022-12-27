// Fill out your copyright notice in the Description page of Project Settings.


#include "RunebreakAPI/RunebreakAPI.h"
#include "HTTP.h"
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
}
