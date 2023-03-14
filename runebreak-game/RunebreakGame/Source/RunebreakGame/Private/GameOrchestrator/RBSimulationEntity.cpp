#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

void* USimulationEntity::GetState(int32 &SizeOUT) {
    SizeOUT = 0;
    return nullptr;
}

FSerializedEntity USimulationEntity::SimSerialize() { 
    FSerializedEntity result;
    result.EntityId = Id;
    result.EntityClass = EntityClass;
    result.ActorClass = ActorClass;
    void* StateRef = GetState(result.Size);
    if (result.Size > 0) {
        memcpy(result.Bytes, StateRef, result.Size);
    }
    return result;
}

void USimulationEntity::SimDeserialize(const FSerializedEntity& SerializedEntity) { 
    Id = SerializedEntity.EntityId;
    EntityClass = SerializedEntity.EntityClass;
    ActorClass = SerializedEntity.ActorClass;

    // this means that state structs need to be of fixed size, for now, or else
    // garbage data could be left over if the serialized struct instance was smaller than
    // the current one.
    int32 Size;
    void* State = GetState(Size);
    if (State != nullptr) {
		memcpy(State, SerializedEntity.Bytes, SerializedEntity.Size);
    }

    if (Size != SerializedEntity.Size) {
        UE_LOG(LogTemp, Fatal, TEXT("mismatched sizes"))
    }
}

void USimulationEntity::InitDefaults() {
}
