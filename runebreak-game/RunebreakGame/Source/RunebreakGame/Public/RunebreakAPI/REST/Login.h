// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>
#include "Login.generated.h"

UINTERFACE(Blueprintable)
class ULoginResultHandler : public UInterface
{
	GENERATED_BODY()
};

class RUNEBREAKGAME_API ILoginResultHandler
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnLoginSuccess();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnLoginFailure();
};


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

UCLASS()
class RUNEBREAKGAME_API ULoginTransaction : public UObject
{
	GENERATED_BODY()

public:
	TFunction<void(FLoginResponseBody)> OnSuccess;

public:
	ULoginTransaction();

	void Login(FString username, FString password);

private:
	void OnLoginResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
