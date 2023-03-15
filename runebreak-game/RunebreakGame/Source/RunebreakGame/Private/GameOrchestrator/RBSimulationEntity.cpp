#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

void USimulationEntity::InitDefaults() {
}

void USimulationEntity::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Serializer->WriteInt(Id);
    Serializer->WriteClass(EntityClass);
    Serializer->WriteClass(ActorClass);
}

void USimulationEntity::DeserializeFromBuffer(unsigned char* buffer, int32* bytes_read) {
    *bytes_read = 0;
    memcpy(&Id, buffer + *bytes_read, sizeof(Id));
    (*bytes_read) += sizeof(Id);
    memcpy(&EntityClass, buffer + *bytes_read, sizeof(EntityClass));
    (*bytes_read) += sizeof(EntityClass);
    memcpy(&ActorClass, buffer + *bytes_read, sizeof(ActorClass));
    (*bytes_read) += sizeof(ActorClass);
}
