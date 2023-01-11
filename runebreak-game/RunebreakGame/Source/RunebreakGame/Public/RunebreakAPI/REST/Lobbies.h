// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>
#include "Lobbies.generated.h"

USTRUCT(BlueprintType)
struct FLobbyUser
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		FString username;
	UPROPERTY(BlueprintReadOnly)
		FString userId;

	FString ToString() {
		return FString(
			+ "\tusername: " + username + "\n"
			+ "\tuserId: " + userId + "\n"
		);
	}
};

USTRUCT(BlueprintType)
struct FLobby
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		FString lobbyName;
	UPROPERTY(BlueprintReadOnly)
		FString lobbyId;
	UPROPERTY(BlueprintReadOnly)
		FString ownerId;
	UPROPERTY(BlueprintReadOnly)
		TArray<FLobbyUser> users;

	FString ToString() {
		return FString(
			+ "\tlobby: " + lobbyId + "\n"
		);
	}
};

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

UINTERFACE(Blueprintable)
class UFetchLobbiesResultHandler : public UInterface
{
	GENERATED_BODY()
};

class RUNEBREAKGAME_API IFetchLobbiesResultHandler
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSuccess(FFetchLobbiesResponseBody response);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnFailure();
};

UCLASS()
class RUNEBREAKGAME_API UFetchLobbiesTransaction : public UObject
{
	GENERATED_BODY()

public:
	TFunction<void(FFetchLobbiesResponseBody)> OnSuccess;

public:
	UFetchLobbiesTransaction();

	void Execute(FString token);

private:
	void OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};

UINTERFACE(Blueprintable)
class ULobbyResultHandler : public UInterface
{
	GENERATED_BODY()
};

class RUNEBREAKGAME_API ILobbyResultHandler
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSuccess(FLobby lobby);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnFailure();
};

UCLASS()
class RUNEBREAKGAME_API UJoinLobbyTransaction : public UObject
{
	GENERATED_BODY()

public:
	TFunction<void(FLobby)> OnSuccess;

public:
	UJoinLobbyTransaction();

	void Execute(FString token, FString lobbyId);

private:
	void OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};

UCLASS()
class RUNEBREAKGAME_API ULeaveLobbyTransaction : public UObject
{
	GENERATED_BODY()

public:
	TFunction<void(FLobby)> OnSuccess;

public:
	ULeaveLobbyTransaction();

	void Execute(FString token, FString lobbyId);

private:
	void OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};

UCLASS()
class RUNEBREAKGAME_API UGetLobbyTransaction : public UObject
{
	GENERATED_BODY()

public:
	TFunction<void(FLobby)> OnSuccess;

public:
	UGetLobbyTransaction();

	void Execute(FString token, FString lobbyId);

private:
	void OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
