// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>
#include "Login.generated.h"


USTRUCT()
struct FLoginRequestBody
{
	GENERATED_BODY()

	UPROPERTY()
		FString username;
	UPROPERTY()
		FString password;

	FLoginRequestBody() {}

	FLoginRequestBody(FString _username, FString _password) {
		username = _username;
		password = _password;
	}

	FString ToString() {
		return FString(
			+ "\tusername: " + username + "\n"
			+ "\tpassword: " + password + '\n'
		);
	}
};

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

FHttpRequestRef DoLoginRESTCall(FString username, FString password, TFunction<void(FLoginResponseBody result)> OnSuccess, TFunction<void()> OnFailure);
