// Fill out your copyright notice in the Description page of Project Settings.


#include "RunebreakAPI/REST/Lobbies.h"

UFetchLobbiesTransaction::UFetchLobbiesTransaction() {

}

void UFetchLobbiesTransaction::Execute(FString token) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UFetchLobbiesTransaction::OnResponseReceived);
	Request->SetURL("http://localhost:9000/lobbies/list");
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("X-Auth-Token", token);
	Request->ProcessRequest();
}

void UFetchLobbiesTransaction::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	FString respJson = *Response->GetContentAsString();
	FFetchLobbiesResponseBody* resp = new FFetchLobbiesResponseBody();
	FromJson(respJson, resp);
	UE_LOG(LogTemp, Warning, TEXT("got response %s"), *respJson);
	OnSuccess(*resp);
}
