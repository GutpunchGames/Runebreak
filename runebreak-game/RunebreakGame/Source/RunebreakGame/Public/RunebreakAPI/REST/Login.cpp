#include <RunebreakGame/Public/RunebreakAPI/REST/Login.h>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>

FHttpRequestRef DoLoginRESTCall(FString username, FString password, TFunction<void(FLoginResponseBody result)> OnSuccess, TFunction<void()> OnFailure) {
	FLoginRequestBody body = FLoginRequestBody(username, password);
	FString serializedRequestBody = ToJsonString(body);
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnFailure](FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
		const int responseCode = Response->GetResponseCode();
		if (bConnectedSuccessfully && responseCode >= 200 && responseCode <= 299) {
			FString respJson = *Response->GetContentAsString();
			FLoginResponseBody resp;
			FromJson(respJson, &resp);
			OnSuccess(resp);
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