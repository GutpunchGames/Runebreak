#pragma once

struct FSerializedEntity {
	int32 EntityType;
	int32 Size;
	char Bytes[64]; // todo: this is just a test

	int32 ComputeChecksum();
};

struct FSerializedSimulation {
	int32 NumEntities;
	FSerializedEntity Entities[32];

	int32 ComputeChecksum();
};
