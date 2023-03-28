// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBGamePrimitives.h"

class GameSimulationSerializer {

public:
	unsigned char Buffer[4096];
	int32 Size = 0;

public:
	bool Serialize(URBGameSimulation* Simulation, unsigned char** buffer, int32* len, int32* checksum);
	void WriteInt(const int32 Value);
	void WriteFloat(const float Value);
	void WriteBytes(void* Bytes, int32 Size);
	void WriteRawClass(UClass Class);
	void WriteString(FString& Value);
	template <typename T> void WriteClass(TSubclassOf<T> Class);
};

class GameSimulationDeserializer {

public:
	unsigned char* Buffer;
	int32 Cursor = 0;

public:
	bool Deserialize(URBGameSimulation* Simulation, unsigned char* buffer, int32 len);
	void ReadInt(int32* Destination);
	void ReadFloat(float* Destination);
	void ReadBytes(void* Destination, int32 NumBytes);
	template <typename T> void ReadClass(TSubclassOf<T>* Destination);
	void ReadRawClass(UClass* Destination);
	FString ReadString();

private:
	uint8 ReadBuffer[64];
};

