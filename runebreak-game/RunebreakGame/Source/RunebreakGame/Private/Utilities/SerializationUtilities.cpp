// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/SerializationUtilities.h"

FString SerializationUtilities::SerializeFVector(const FVector& Vector) {
	FString SerializedVector = FString::Printf(TEXT("%f,%f,%f"), Vector.X, Vector.Y, Vector.Z);
	return SerializedVector;
}

FVector SerializationUtilities::DeserializeFVector(const FString& Bytes) {
	TArray<FString> DeserializedBytes;

	Bytes.ParseIntoArray(DeserializedBytes, TEXT(","), true);

	FVector Vector;

	Vector.X = FCString::Atof(*DeserializedBytes[0]);
	Vector.Y = FCString::Atof(*DeserializedBytes[1]);
	Vector.Z = FCString::Atof(*DeserializedBytes[2]);

	return Vector;
}

