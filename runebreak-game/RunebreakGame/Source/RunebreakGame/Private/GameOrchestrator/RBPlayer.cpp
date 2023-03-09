#include "GameOrchestrator/RBPlayer.h"

void URBPlayer::Initialize(FPosition Position, int32 PlayerIndex) {
    State.Position = Position;
    State.PlayerIndex = PlayerIndex;
}

void URBPlayer::SimulationTick(URBGameSimulation* Simulation) {
    int Inputs = Simulation->_inputs[State.PlayerIndex];
    int MoveUp = Inputs & INPUT_MOVE_UP;
    int MoveDown = Inputs & INPUT_MOVE_DOWN;
    if (MoveUp) {
		State.Position.y = State.Position.y + 10;
    }
    else if (MoveDown) {
		State.Position.y = State.Position.y - 10;
    }
};

FSerializedEntity URBPlayer::Serialize() {
    FSerializedEntity result;
    result.EntityType = 0;
    result.Size = sizeof(State);
    memcpy(result.Bytes, &State, result.Size);
    return result;
}

void URBPlayer::Deserialize(FSerializedEntity SerializedEntity) {
    memcpy(&State, SerializedEntity.Bytes, SerializedEntity.Size);
}
