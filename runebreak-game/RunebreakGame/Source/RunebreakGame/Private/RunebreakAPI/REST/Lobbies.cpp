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

UGetLobbyTransaction::UGetLobbyTransaction() {

}

void UGetLobbyTransaction::Execute(FString token, FString lobbyId) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGetLobbyTransaction::OnResponseReceived);
	Request->SetURL("http://localhost:9000/lobbies");
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("X-Auth-Token", token);
	Request->SetContentAsString("{\"lobbyId\":\"" + lobbyId + "\"}");
	Request->ProcessRequest();
}

void UGetLobbyTransaction::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	FString respJson = *Response->GetContentAsString();
	FLobby* resp = new FLobby();
	FromJson(respJson, resp);
	UE_LOG(LogTemp, Warning, TEXT("got response %s"), *respJson);
	OnSuccess(*resp);
}

UJoinLobbyTransaction::UJoinLobbyTransaction() {

}

void UJoinLobbyTransaction::Execute(FString token, FString lobbyId) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UJoinLobbyTransaction::OnResponseReceived);
	Request->SetURL("http://localhost:9000/lobbies/join");
	Request->SetVerb("PATCH");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("X-Auth-Token", token);
	Request->SetContentAsString("{\"lobbyId\":\"" + lobbyId + "\"}");
	Request->ProcessRequest();
}

void UJoinLobbyTransaction::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	FString respJson = *Response->GetContentAsString();
	FLobby* resp = new FLobby();
	FromJson(respJson, resp);
	UE_LOG(LogTemp, Warning, TEXT("got response %s"), *respJson);
	OnSuccess(*resp);
}

ULeaveLobbyTransaction::ULeaveLobbyTransaction() {

}

void ULeaveLobbyTransaction::Execute(FString token, FString lobbyId) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ULeaveLobbyTransaction::OnResponseReceived);
	Request->SetURL("http://localhost:9000/lobbies/leave");
	Request->SetVerb("PATCH");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetHeader("X-Auth-Token", token);
	Request->SetContentAsString("{\"lobbyId\":\"" + lobbyId + "\"}");
	Request->ProcessRequest();
}

void ULeaveLobbyTransaction::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	FString respJson = *Response->GetContentAsString();
	FLobby* resp = new FLobby();
	FromJson(respJson, resp);
	UE_LOG(LogTemp, Warning, TEXT("got response %s"), *respJson);
	OnSuccess(*resp);
}
