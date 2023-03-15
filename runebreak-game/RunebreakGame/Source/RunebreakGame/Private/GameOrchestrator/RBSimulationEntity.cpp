#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

void USimulationEntity::InitDefaults() {
}

void USimulationEntity::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Serializer->WriteInt(Id);
    Serializer->WriteClass<USimulationEntity>(EntityClass);
    Serializer->WriteClass<ASimulationActor>(ActorClass);
}

void USimulationEntity::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Deserializer->ReadInt(&Id);
    Deserializer->ReadClass<USimulationEntity>(&EntityClass);
    Deserializer->ReadClass<ASimulationActor>(&ActorClass);
}
