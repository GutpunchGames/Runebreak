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

struct FSimulationEntity {
	int32 Id;

	virtual void Serialize(void* OutState, int32* Size);
	virtual void SimulationTick(FRBGameSimulation* Simulation);
};

struct FRBPlayer : public FSimulationEntity {
	FPosition position;
	FVelocity velocity;
	int32 PlayerIndex;

	virtual void SimulationTick(FRBGameSimulation* Simulation) override;
};

struct FRBGameSimulation {
	int	_framenumber;
	FRBPlayer _players[2];
	int32 _inputs[2];

	void Init();
	void Update(int inputs[], int disconnect_flags);
};
