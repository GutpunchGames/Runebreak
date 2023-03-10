#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::SimulationTick(URBGameSimulation* Simulation) { }

FSerializedEntity USimulationEntity::Serialize() { 
    FSerializedEntity result;
    result.EntityType = -1;
    result.Size = 0;
    return result;
}

void USimulationEntity::Deserialize(FSerializedEntity SerializedEntity) { }

void USimulationEntity::InitDefaults() {
}
