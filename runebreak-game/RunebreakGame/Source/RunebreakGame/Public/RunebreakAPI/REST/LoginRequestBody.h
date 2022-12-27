// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "LoginRequestBody.generated.h"

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
