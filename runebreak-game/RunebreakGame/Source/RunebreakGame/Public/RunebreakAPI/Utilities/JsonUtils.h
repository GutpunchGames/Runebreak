#pragma once

#include "CoreMinimal.h"

#include <string>
#include <Runtime/JsonUtilities/Public/JsonObjectConverter.h>

template<typename InStructType>
static TSharedPtr<FJsonObject> ToJsonObject(InStructType& inStruct) {
	return FJsonObjectConverter::UStructToJsonObject(inStruct);
}

// todo: add better error handling?
template<typename OutStructType>
static void FromJson(FString json, OutStructType* outStruct, bool crashOnError=true) {
	const bool success = FJsonObjectConverter::JsonObjectStringToUStruct(json, outStruct);
	if (!success && crashOnError) {
		UE_LOG(LogTemp, Fatal, TEXT("got error deserializing"));
	}
}
