#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::SetupStates(URBGameSimulation* Simulation) {
    StateMachine = NewObject<UEntityStateMachine>(this, FName("EntityStateMachine"));
    StateMachine->Simulation = Simulation;
}

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

void USimulationEntity::InitDefaults() {
}

void USimulationEntity::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Serializer->WriteInt(Id);
    Serializer->WriteClass<USimulationEntity>(EntityClass);
    Serializer->WriteClass<ASimulationActor>(ActorClass);
    FString StateName = StateMachine->GetState()->Name;
    Serializer->WriteString(StateName);
    Serializer->WriteInt(StateMachine->GetState()->Frame);
}

void USimulationEntity::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Deserializer->ReadInt(&Id);
    Deserializer->ReadClass<USimulationEntity>(&EntityClass);
    Deserializer->ReadClass<ASimulationActor>(&ActorClass);
    int32 StateFrame;
    FString StateName = Deserializer->ReadString();
    Deserializer->ReadInt(&StateFrame);

    StateMachine->SkipToStateByName(StateName, StateFrame);
}
