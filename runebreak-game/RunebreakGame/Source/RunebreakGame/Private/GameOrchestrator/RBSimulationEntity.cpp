#include "GameOrchestrator/RBSimulationEntity.h"

void FSimulationEntity::SimulationTick(FRBGameSimulation* Simulation) { }
FSerializedEntity FSimulationEntity::Serialize() { 
    FSerializedEntity result;
    result.EntityType = -1;
    result.Size = 0;
    return result;
}

void FSimulationEntity::Deserialize(FSerializedEntity SerializedEntity) { }
