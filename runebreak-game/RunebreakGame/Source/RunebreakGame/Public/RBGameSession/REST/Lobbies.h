// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include <RunebreakGame/Public/RBGameSession/Utilities/JsonUtils.h>
#include <RunebreakGame/Public/RBGameSession/Types/LobbyTypes.h>
#include "Lobbies.generated.h"

USTRUCT(BlueprintType)
struct FFetchLobbiesResponseBody
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		TArray<FLobby> lobbies;

	FString ToString() {
		return FString(
			+ "\tfirst lobby: " + lobbies[0].ToString() + "\n"
		);
	}
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLobbiesFetched, FFetchLobbiesResponseBody, Lobbies);
FHttpRequestRef GetLobbiesRESTCall(TFunction<void(FFetchLobbiesResponseBody resp)> OnSuccess, TFunction<void()> OnFailure);

FHttpRequestRef GetLobbyRESTCall(FString lobbyId, TFunction<void(FLobby lobby)> OnSuccess, TFunction<void()> OnFailure);
FHttpRequestRef JoinLobbyRESTCall(FString lobbyId, TFunction<void(FLobby lobby)> OnSuccess, TFunction<void()> OnFailure);
FHttpRequestRef LeaveLobbyRESTCall(FString lobbyId, TFunction<void(FLobby lobby)> OnSuccess, TFunction<void()> OnFailure);
