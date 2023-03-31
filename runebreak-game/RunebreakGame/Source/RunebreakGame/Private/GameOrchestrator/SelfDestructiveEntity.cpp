#include "GameOrchestrator/SelfDestructiveEntity.h"

void USelfDestructiveEntity::InitDefaults() {
    Position.x = 0;
    Position.y = 0;
    State.TimeAlive = 0;

    State.MoveSpeed = Defaults.MoveSpeed;
    State.TimeToLive = Defaults.TimeToLive;
}

void USelfDestructiveEntity::SetupStates(URBGameSimulation* Simulation) {
    Super::SetupStates(Simulation);
    StateMachine->AddState("Move", NewObject<USelfDestructiveEntity_Move>(this, FName("Move")));
}

void USelfDestructiveEntity::Act(URBGameSimulation* Simulation) {
    StateMachine->TickState(this);
}

void USelfDestructiveEntity::ActivateDetectionBoxes(URBGameSimulation* Simulation) {
    Simulation->ActivateDetectionBox(Id, Position.x, Position.y, 60, 60, DetectionBoxType::Hitbox);
}

void USelfDestructiveEntity_Move::TickState(USimulationEntity* Owner) {
    USelfDestructiveEntity* Entity = Cast<USelfDestructiveEntity>(Owner);
    FSelfDestructiveEntityState* State = &(Entity->State);
    Entity->Position.x = Entity->Position.x + State->MoveSpeed;
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

