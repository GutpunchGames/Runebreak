// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HTTP.h"
#include "RestCallExperiments.generated.h"

USTRUCT()
struct FLoginExperimentRequestBody
{
	GENERATED_BODY()

		UPROPERTY()
		FString username;
	UPROPERTY()
		FString password;

	FLoginExperimentRequestBody() {}

	FLoginExperimentRequestBody(FString _username, FString _password) {
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

FHttpRequestRef _DoTestLoginCall(FString username, FString password, TFunctionRef<void ()> OnSuccess, TFunctionRef<void ()> OnFailure);
