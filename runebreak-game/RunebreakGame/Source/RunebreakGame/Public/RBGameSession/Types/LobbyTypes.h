// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RunebreakGame/Public/RBGameSession/Types/UserTypes.h>
#include "LobbyTypes.generated.h"

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
		TArray<FUser> users;

	bool IsValid() {
		return !(lobbyId.Equals(""));
	}

	bool Invalidate() {
		bool WasValid = IsValid();
		lobbyId = "";
		return WasValid;
	}

	FString ToString() {
		return FString(
			+ "\tlobby: " + lobbyId + "\n"
		);
	}

	void PrintUsers() {
		UE_LOG(LogTemp, Warning, TEXT("users size: %d"), users.Num());
		for (FUser User : users) {
			UE_LOG(LogTemp, Warning, TEXT("lobby user: %s"), *User.ToString());
		}
	}
};

