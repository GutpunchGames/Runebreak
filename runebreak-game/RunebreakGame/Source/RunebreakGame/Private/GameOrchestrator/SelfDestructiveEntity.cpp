#include "GameOrchestrator/SelfDestructiveEntity.h"

void USelfDestructiveEntity::InitDefaults() {
    State.Position.x = 0;
    State.Position.y = 100;
    State.TimeAlive = 0;

    State.MoveSpeed = Defaults.MoveSpeed;
    State.TimeToLive = Defaults.TimeToLive;
}

void USelfDestructiveEntity::SetupStates() {
    Super::SetupStates();
    StateMachine->AddState("Move", NewObject<USelfDestructiveEntity_Move>(this, FName("Move")));
}

void USelfDestructiveEntity::Act(URBGameSimulation* Simulation) {
    StateMachine->TickState(this, Simulation);
}

void USelfDestructiveEntity_Move::TickState(USimulationEntity* Owner, URBGameSimulation* Simulation) {
    USelfDestructiveEntity* Entity = Cast<USelfDestructiveEntity>(Owner);
    FSelfDestructiveEntityState* State = &(Entity->State);
    State->Position.x = State->Position.x + State->MoveSpeed;
    State->TimeAlive = State->TimeAlive + 1;

    if (State->TimeAlive > State->TimeToLive) {
        Simulation->RemoveEntity(Owner->Id);
    }
}

void USelfDestructiveEntity::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Super::SerializeToBuffer(Serializer);
    Serializer->WriteBytes(&State, sizeof(State));
}

void USelfDestructiveEntity::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Super::DeserializeFromBuffer(Deserializer);
    Deserializer->ReadBytes(&State, sizeof(State));
}

