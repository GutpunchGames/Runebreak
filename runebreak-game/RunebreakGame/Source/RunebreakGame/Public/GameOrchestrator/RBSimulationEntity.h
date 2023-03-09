#pragma once

#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"

struct FSimulationEntity {
	int32 Id;

	virtual void SimulationTick(URBGameSimulation* Simulation);
	virtual FSerializedEntity Serialize();
	virtual void Deserialize(FSerializedEntity SerializedEntity);
};
