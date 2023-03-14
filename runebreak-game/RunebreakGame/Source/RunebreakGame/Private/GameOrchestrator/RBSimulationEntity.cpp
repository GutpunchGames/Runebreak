#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

void USimulationEntity::InitDefaults() {
}

void USimulationEntity::SerializeToBuffer(unsigned char* buffer, int32* bytes_written) {
    *bytes_written = 0;
    memcpy(buffer + *bytes_written, &Id, sizeof(Id));
    (*bytes_written) += sizeof(Id);
    memcpy(buffer + *bytes_written, &EntityClass, sizeof(EntityClass));
    UE_LOG(LogTemp, Warning, TEXT("Serialized class type: %s"), *(EntityClass->GetName()))
    (*bytes_written) += sizeof(EntityClass);
    memcpy(buffer + *bytes_written, &ActorClass, sizeof(ActorClass));
    (*bytes_written) += sizeof(ActorClass);
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
