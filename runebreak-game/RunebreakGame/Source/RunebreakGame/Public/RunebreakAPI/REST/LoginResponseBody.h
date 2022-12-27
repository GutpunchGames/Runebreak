// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>
#include "LoginResponseBody.generated.h"

USTRUCT()
struct FLoginResponseBody
{
	GENERATED_BODY()

	UPROPERTY()
		FString userId;
	UPROPERTY()
		FString token;

	FLoginResponseBody() {}

	FLoginResponseBody(FString _userId, FString _token) {
		userId = _userId;
		token = _token;
	}

	FString ToString() {
		return FString(
			+ "\tuserId: " + userId + "\n"
			+ "\ttoken: " + token + '\n'
		);
	}
};
