#include "GameOrchestrator/RBSimulationEntity.h"

USimulationEntity::USimulationEntity() {
    StateMachine = CreateDefaultSubobject<UEntityStateMachine>(FName("EntityStateMachine"));
}

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

void USimulationEntity::InitDefaults() {
}

void USimulationEntity::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Serializer->WriteInt(Id);
    Serializer->WriteClass<USimulationEntity>(EntityClass);
    Serializer->WriteClass<ASimulationActor>(ActorClass);
    Serializer->WriteBytes(&(StateMachine->GetState()->Name), 8);
    Serializer->WriteInt(StateMachine->GetState()->Frame);
}

void USimulationEntity::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Deserializer->ReadInt(&Id);
    Deserializer->ReadClass<USimulationEntity>(&EntityClass);
    Deserializer->ReadClass<ASimulationActor>(&ActorClass);
    FString StateName("", 8);
    int32 StateFrame;
    Deserializer->ReadBytes(&StateName, 8);
    Deserializer->ReadInt(&StateFrame);

    StateMachine->SkipToStateByName(StateName, StateFrame);
}
