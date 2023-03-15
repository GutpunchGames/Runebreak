#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

void USimulationEntity::InitDefaults() {
}

void USimulationEntity::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Serializer->WriteInt(Id);
    Serializer->WriteBytes(&EntityClass, sizeof(EntityClass));
    Serializer->WriteBytes(&ActorClass, sizeof(ActorClass));
}

void USimulationEntity::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Deserializer->ReadInt(&Id);
    Deserializer->ReadBytes(&EntityClass, sizeof(EntityClass));
    Deserializer->ReadBytes(&ActorClass, sizeof(ActorClass));
}
