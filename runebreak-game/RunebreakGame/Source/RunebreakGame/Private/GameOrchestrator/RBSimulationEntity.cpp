#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

FSerializedEntity USimulationEntity::SimSerialize() { 
    FSerializedEntity result;
    result.EntityId = Id;
    result.EntityClass = EntityClass;
    result.ActorClass = ActorClass;
    return result;
}

void USimulationEntity::SimDeserialize(FSerializedEntity SerializedEntity) { 
    Id = SerializedEntity.EntityId;
    EntityClass = SerializedEntity.EntityClass;
    ActorClass = SerializedEntity.ActorClass;
}

void USimulationEntity::InitDefaults() {
}
