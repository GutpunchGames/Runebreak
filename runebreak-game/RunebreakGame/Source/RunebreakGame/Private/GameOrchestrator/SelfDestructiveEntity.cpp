#include "GameOrchestrator/SelfDestructiveEntity.h"

void USelfDestructiveEntity::InitDefaults() {
    State.Position.x = 0;
    State.Position.y = 0;
    State.TimeAlive = 0;

    State.MoveSpeed = Defaults.MoveSpeed;
    State.TimeToLive = Defaults.TimeToLive;
}

void USelfDestructiveEntity::Act(URBGameSimulation* Simulation) {
    State.Position.x = State.Position.x + State.MoveSpeed;
    State.TimeAlive = State.TimeAlive + 1;

    if (State.TimeAlive > State.TimeToLive) {
        Simulation->RemoveEntity(Id);
    }
}

FSerializedEntity USelfDestructiveEntity::SimSerialize() {
    FSerializedEntity result = Super::SimSerialize();
    result.Size = sizeof(State);
    memcpy(result.Bytes, &State, result.Size);
    return result;
}

void USelfDestructiveEntity::SimDeserialize(FSerializedEntity SerializedEntity) {
    Super::SimDeserialize(SerializedEntity);
    memcpy(&State, SerializedEntity.Bytes, SerializedEntity.Size);
}
