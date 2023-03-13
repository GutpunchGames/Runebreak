#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

FSerializedEntity USimulationEntity::SimSerialize() { 
    FSerializedEntity result;
    result.EntityType = -1;
    result.Size = 0;
    return result;
}

void USimulationEntity::SimDeserialize(FSerializedEntity SerializedEntity) { }

void USimulationEntity::InitDefaults() {
}
