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
    FString StateName = StateMachine->GetState()->Name;
    UE_LOG(LogTemp, Warning, TEXT("Writing StateName: %s"), *StateName)
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

    UE_LOG(LogTemp, Warning, TEXT("Deserialize Checkpoint. Name: %s -- Frame: %d"), *StateName, StateFrame)
    StateMachine->SkipToStateByName(StateName, StateFrame);
}
