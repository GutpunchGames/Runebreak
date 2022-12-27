// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include <string>
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>
#include "LoginRequestBody.generated.h"

USTRUCT()
struct FLoginRequestBody
{
	GENERATED_BODY()

	UPROPERTY()
		FString username;
	UPROPERTY()
		FString password;

	FString ToString() {
		return FString(
			+ "\tusername: " + username + "\n"
			+ "\tpassword: " + password + '\n'
		);
	}

	static FJsonObject ToJsonObject(FLoginRequestBody body) {
		TSharedPtr<FJsonObject> jsonObj = FJsonObjectConverter::UStructToJsonObject(body);
		return *jsonObj;
	}

	static FLoginRequestBody FromJson(FString json) {
		FLoginRequestBody requestBody;

		if (!FJsonObjectConverter::JsonObjectStringToUStruct(json, &requestBody)) {
			UE_LOG(LogTemp, Fatal, TEXT("got error deserializing"));
		}

		return requestBody;
	}

	static void FromJson_TEST() {
		FString json = FString("{\"username\":\"andy\", \"password\":\"pwpwpw\"}");
		FLoginRequestBody requestBody = FLoginRequestBody::FromJson(json);
		UE_LOG(LogTemp, Warning, TEXT("deserialized: %s"), *requestBody.ToString());
	}

	static void ToJson_TEST() {
		FLoginRequestBody body;
		body.username = "username";
		body.password = "pwpwpw";
		FJsonObject t = ToJsonObject(body);
		FString deserializedUsername = t.GetStringField("username");
		FString deserializedPassword = t.GetStringField("password");
		FString msg = FString("deserialized username: " + deserializedUsername + " -- deserialized password: " + deserializedPassword);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
	}
};
