#pragma once

#include "CoreMinimal.h"

#include <string>
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>

template<typename InStructType>
static TSharedPtr<FJsonObject> ToJsonObject(InStructType& inStruct) {
	return FJsonObjectConverter::UStructToJsonObject(inStruct);
}

template<typename InStructType>
static FString ToJsonString(InStructType& inStruct) {
	TSharedPtr<FJsonObject> jsonObj = FJsonObjectConverter::UStructToJsonObject(inStruct);
	TSharedRef<FJsonObject> sharedRef = jsonObj.ToSharedRef();

	FString jsonStr;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&jsonStr);
	FJsonSerializer::Serialize(sharedRef, Writer);
	return jsonStr;
}

// todo: add better error handling?
template<typename OutStructType>
static void FromJson(FString json, OutStructType* outStruct, bool crashOnError=true) {
	const bool success = FJsonObjectConverter::JsonObjectStringToUStruct(json, outStruct);
	if (!success && crashOnError) {
		UE_LOG(LogTemp, Fatal, TEXT("got error deserializing"));
	}
}
