#pragma once

#include "CoreMinimal.h"

// forward declaration
struct FRBGameSimulation;

struct FPosition {
	double x;
	double y;
};

struct FVelocity {
	double dx;
	double dy;
};

struct FSerializedEntity {
	int32 EntityType;
	int32 Size;
	char Bytes[64]; // todo: this is just a test

	int32 ComputeChecksum();
};

struct FSimulationEntity {
	int32 Id;

	virtual void SimulationTick(FRBGameSimulation* Simulation);
	virtual FSerializedEntity Serialize();
	virtual void Deserialize(FSerializedEntity SerializedEntity);
};

struct FRBPlayer : public FSimulationEntity {
	FPosition position;
	int32 PlayerIndex;

	virtual void SimulationTick(FRBGameSimulation* Simulation) override;
	virtual FSerializedEntity Serialize() override;
	virtual void Deserialize(FSerializedEntity SerializedEntity) override;
};

struct FSerializedSimulation {
	int32 NumEntities;
	FSerializedEntity Entities[32];

	int32 ComputeChecksum();
};

struct FRBGameSimulation {
	int	_framenumber;
	int NumEntities;
	FSimulationEntity* Entities[2];
	int32 _inputs[2];

	void Init();
	void Update(int inputs[], int disconnect_flags);
	FRBPlayer* GetPlayer(int PlayerId);

	bool Save(unsigned char** buffer, int32* len, int32* checksum);
	bool Load(unsigned char* buffer, int32 len);
};
