#pragma once

#include "CoreMinimal.h"

#include <string>
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>

template<typename InStructType>
static FJsonObject ToJsonObject(InStructType& inStruct) {
	TSharedPtr<FJsonObject> jsonObj = FJsonObjectConverter::UStructToJsonObject(inStruct);
	return *jsonObj;
}

// todo: add better error handling?
template<typename OutStructType>
static void FromJson(FString json, OutStructType* outStruct, bool crashOnError=true) {
	const bool success = FJsonObjectConverter::JsonObjectStringToUStruct(json, outStruct);
	if (!success && crashOnError) {
		UE_LOG(LogTemp, Fatal, TEXT("got error deserializing"));
	}
}
