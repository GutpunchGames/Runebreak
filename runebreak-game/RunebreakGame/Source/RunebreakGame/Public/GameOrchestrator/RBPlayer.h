#pragma once

#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "GameOrchestrator/RBSimulationEntity.h"

struct FRBPlayer : public FSimulationEntity {
	FPosition position;
	int32 PlayerIndex;

	virtual void SimulationTick(FRBGameSimulation* Simulation) override;
	virtual FSerializedEntity Serialize() override;
	virtual void Deserialize(FSerializedEntity SerializedEntity) override;
};
