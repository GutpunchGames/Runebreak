// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBGamePrimitives.h"

class GameSimulationSerializer {

public:
	unsigned char Buffer[4096];
	int32 Size;

public:
	bool Serialize(URBGameSimulation* Simulation, unsigned char** buffer, int32* len, int32* checksum);
	void WriteInt(const int32 Value);
	void WriteClass(UClass* Class);
	void WriteBytes(void* Bytes, int32 Size);
};

class GameSimulationDeserializer {

public:
	unsigned char* Buffer;
	int32 Cursor = 0;

public:
	bool Deserialize(URBGameSimulation* Simulation, unsigned char* buffer, int32 len);
	int32 PeekInt();
	UClass* PeekClass();
	void ReadInt(int32* Destination);
	void ReadClass(UClass** Destination);
	void ReadBytes(void* Destination, int32 NumBytes);
};

