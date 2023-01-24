// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/Base64Utilities.h"

FString Base64Utilities::Base64Encode(const FString& Source) {
	TArray<uint8> ByteArray;
	FTCHARToUTF8 StringSrc = FTCHARToUTF8(Source.GetCharArray().GetData());
	ByteArray.Append((uint8*)StringSrc.Get(), StringSrc.Length());
	return FBase64::Encode(ByteArray);
}

FString Base64Utilities::Base64Decode(const FString& Source) {
	FString Dest;
	TArray<uint8> ByteArray;
	bool Success = FBase64::Decode(Source, Dest);
	return Dest;
}
