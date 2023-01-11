// Fill out your copyright notice in the Description page of Project Settings.


#include "Sandbox/RestCallExperiments.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>

FHttpRequestRef _DoTestLoginCall(FString username, FString password, TFunctionRef<void ()> OnSuccess, TFunctionRef<void ()> OnFailure) {
	FLoginExperimentRequestBody body = FLoginExperimentRequestBody(username, password);
	FString serializedRequestBody = ToJsonString(body);
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

	Request->SetURL("http://localhost:9000/login");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(serializedRequestBody);
	Request->ProcessRequest();
	return Request;
}
