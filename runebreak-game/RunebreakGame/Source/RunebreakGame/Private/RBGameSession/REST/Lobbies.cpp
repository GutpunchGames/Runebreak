// Fill out your copyright notice in the Description page of Project Settings.


#include "RBGameSession/REST/Lobbies.h"

FHttpRequestRef GetLobbiesRESTCall(TFunction<void(FFetchLobbiesResponseBody resp)> OnSuccess, TFunction<void()> OnFailure) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnFailure](FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
		const int responseCode = Response->GetResponseCode();
		if (bConnectedSuccessfully && responseCode >= 200 && responseCode <= 299) {
			FString respJson = *Response->GetContentAsString();
			FFetchLobbiesResponseBody resp;
			FromJson(respJson, &resp);
			OnSuccess(resp);
		}
		else {
			OnFailure();
		}
	});

	Request->SetURL("http://localhost:9000/lobbies/list");
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", "application/json");
	return Request;
}

FHttpRequestRef GetLobbyRESTCall(FString lobbyId, TFunction<void(FLobby lobby)> OnSuccess, TFunction<void()> OnFailure) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnFailure](FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
		const int responseCode = Response->GetResponseCode();
		if (bConnectedSuccessfully && responseCode >= 200 && responseCode <= 299) {
			FString respJson = *Response->GetContentAsString();
			FLobby resp;
			FromJson(respJson, &resp);
			OnSuccess(resp);
		}
		else {
			OnFailure();
		}
	});

	Request->SetURL("http://localhost:9000/lobbies");
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString("{\"lobbyId\":\"" + lobbyId + "\"}");
	return Request;
}

FHttpRequestRef CreateLobbyRESTCall(FString LobbyName, TFunction<void(FLobby lobby)> OnSuccess, TFunction<void()> OnFailure) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnFailure](FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
		const int responseCode = Response->GetResponseCode();
		if (bConnectedSuccessfully && responseCode >= 200 && responseCode <= 299) {
			FString respJson = *Response->GetContentAsString();
			FCreateOrJoinLobbyResponseBody resp;
			FromJson(respJson, &resp);
			OnSuccess(resp.lobby);
		}
		else {
			OnFailure();
		}
	});

	Request->SetURL("http://localhost:9000/lobbies");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString("{\"lobbyName\":\"" + LobbyName + "\"}");
	return Request;
}

FHttpRequestRef JoinLobbyRESTCall(FString lobbyId, TFunction<void(FLobby lobby)> OnSuccess, TFunction<void()> OnFailure) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnFailure](FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
		const int responseCode = Response->GetResponseCode();
		if (bConnectedSuccessfully && responseCode >= 200 && responseCode <= 299) {
			FString respJson = *Response->GetContentAsString();
			FLobby resp;
			FromJson(respJson, &resp);
			OnSuccess(resp);
		}
		else {
			OnFailure();
		}
	});

	Request->SetURL("http://localhost:9000/lobbies/join");
	Request->SetVerb("PATCH");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString("{\"lobbyId\":\"" + lobbyId + "\"}");
	return Request;
}

FHttpRequestRef LeaveLobbyRESTCall(FString lobbyId, TFunction<void()> OnSuccess, TFunction<void()> OnFailure) {
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnFailure](FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
		const int responseCode = Response->GetResponseCode();
		if (bConnectedSuccessfully && responseCode >= 200 && responseCode <= 299) {
			OnSuccess();
		}
		else {
			OnFailure();
		}
	});

	Request->SetURL("http://localhost:9000/lobbies/leave");
	Request->SetVerb("PATCH");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString("{\"lobbyId\":\"" + lobbyId + "\"}");
	return Request;
}

