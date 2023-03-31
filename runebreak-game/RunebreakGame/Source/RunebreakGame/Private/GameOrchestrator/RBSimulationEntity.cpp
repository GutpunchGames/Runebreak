#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::SetupStates(URBGameSimulation* Simulation) {
    StateMachine = NewObject<UEntityStateMachine>(this, FName("EntityStateMachine"));
    StateMachine->Simulation = Simulation;
}

void USimulationEntity::SimulationTick(URBGameSimulation* Simulation) { 
    Act(Simulation);
    ActivateDetectionBoxes(Simulation);
}

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ActivateDetectionBoxes(URBGameSimulation* Simulation) { }

void USimulationEntity::ResolveCollisions(URBGameSimulation* Simulation) { }

void USimulationEntity::InitDefaults() { }

void USimulationEntity::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Serializer->WriteInt(Id);
    Serializer->WriteClass<USimulationEntity>(EntityClass);
    Serializer->WriteClass<ASimulationActor>(ActorClass);
    FString StateName = StateMachine->GetState()->Name;
    Serializer->WriteString(StateName);
    Serializer->WriteInt(StateMachine->GetState()->Frame);
    Serializer->WriteFloat(Position.x);
    Serializer->WriteFloat(Position.y);
}

void USimulationEntity::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Deserializer->ReadInt(&Id);
    Deserializer->ReadClass<USimulationEntity>(&EntityClass);
    Deserializer->ReadClass<ASimulationActor>(&ActorClass);
    int32 StateFrame;
    FString StateName = Deserializer->ReadString();
    Deserializer->ReadInt(&StateFrame);

    StateMachine->SkipToStateByName(StateName, StateFrame);
    Deserializer->ReadFloat(&(Position.x));
    Deserializer->ReadFloat(&(Position.y));
}

void USimulationEntity::Move(const int32& X, const int32& Y) {
	Position.x = Position.x + X;
	Position.y = Position.y + Y;
}

