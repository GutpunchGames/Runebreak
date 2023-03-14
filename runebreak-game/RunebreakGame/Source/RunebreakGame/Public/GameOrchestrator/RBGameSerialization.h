#pragma once

struct FSerializedEntity {
	TSubclassOf<USimulationEntity> EntityClass;
	TSubclassOf<ASimulationActor> ActorClass;
	int32 EntityId;
	int32 Size;
	char Bytes[64]; // todo: this is just a test
};

struct FSerializedSimulation {
	int32 NumEntities;
	FSerializedEntity Entities[32];
};
