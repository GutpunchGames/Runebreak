#include <RunebreakGame/Public/RunebreakAPI/REST/Login.h>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTP.h"
#include <RunebreakGame/Public/RunebreakAPI/Utilities/JsonUtils.h>

ULoginTransaction::ULoginTransaction() {

}

void ULoginTransaction::Login() {
	FLoginRequestBody body = FLoginRequestBody("andy2", "password");
	TSharedPtr<FJsonObject> requestJsonObject = ToJsonObject(body);
	UE_LOG(LogTemp, Warning, TEXT("got json: %s"), *(*requestJsonObject).GetStringField("username"))
	TSharedRef<FJsonObject> test = requestJsonObject.ToSharedRef();

	FString serializedRequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&serializedRequestBody);
	FJsonSerializer::Serialize(test, Writer);

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ULoginTransaction::OnLoginResponseReceived);
	Request->SetURL("http://localhost:9000/login");
	Request->SetContentAsString(serializedRequestBody);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

void ULoginTransaction::OnLoginResponseReceived(FHttpRequestPtr request, FHttpResponsePtr Response, bool bConnectedSuccessfully) {
	FString respJson = *Response->GetContentAsString();
	FLoginResponseBody* resp = new FLoginResponseBody();
	FromJson(respJson, resp);
	UE_LOG(LogTemp, Warning, TEXT("deserialized resp successfully with userId: %s"), *resp->userId);
	OnSuccess(*resp);
}