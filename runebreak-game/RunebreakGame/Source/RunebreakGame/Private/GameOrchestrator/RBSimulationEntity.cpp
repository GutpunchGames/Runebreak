#include "GameOrchestrator/RBSimulationEntity.h"

void USimulationEntity::SetupStates(URBGameSimulation* Simulation) {
    StateMachine = NewObject<UEntityStateMachine>(this, FName("EntityStateMachine"));
    StateMachine->Simulation = Simulation;

    for (const auto& Iterator : StatePrototypes) {
        FName Name = Iterator.Key;
		UEntityState* State = NewObject<UEntityState>(this, Iterator.Value);
        State->Name = Name.ToString();
        State->LoadDetectionBoxes();
		StateMachine->AddState(State->Name, State);
    }
}

void USimulationEntity::SimulationTick(URBGameSimulation* Simulation) { 
    Act(Simulation);
    ActivateDetectionBoxes(Simulation);
}

void USimulationEntity::Act(URBGameSimulation* Simulation) { }

void USimulationEntity::ActivateDetectionBoxes(URBGameSimulation* Simulation) {
	UEntityState* CurrentState = StateMachine->CurrentState;
    if (CurrentState->StateDetectionBoxes.DetectionBoxesByFrame.Num() <= 0) {
        return;
    }

    for (const FDetectionBoxConfig& BoxConfig : CurrentState->StateDetectionBoxes.DetectionBoxesByFrame[CurrentState->Frame].DetectionBoxes) {
		Simulation->ActivateDetectionBox(Id, Position.x + BoxConfig.Offset.X, Position.y + BoxConfig.Offset.Y, BoxConfig.Size.X, BoxConfig.Size.Y, BoxConfig.Type);
    }
}

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

