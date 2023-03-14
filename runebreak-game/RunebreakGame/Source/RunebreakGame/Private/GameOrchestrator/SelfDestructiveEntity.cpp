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

void USelfDestructiveEntity::SerializeToBuffer(unsigned char* buffer, int32* bytes_written) {
    Super::SerializeToBuffer(buffer, bytes_written);
    memcpy(buffer + *bytes_written, &State, sizeof(State));
    *(bytes_written) += sizeof(State);
}

void USelfDestructiveEntity::DeserializeFromBuffer(unsigned char* buffer, int32* bytes_read) {
    Super::DeserializeFromBuffer(buffer, bytes_read);
    memcpy(&State, buffer + *bytes_read, sizeof(State));
    *(bytes_read) += sizeof(State);
}
