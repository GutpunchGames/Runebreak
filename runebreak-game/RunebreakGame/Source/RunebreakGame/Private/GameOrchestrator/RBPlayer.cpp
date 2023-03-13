#include "GameOrchestrator/RBPlayer.h"

void URBPlayer::Initialize(int32 PlayerIndex) {
    State.Position.x = PlayerIndex == 0 ? -100 : 100;
	State.PlayerIndex = PlayerIndex;
	State.MoveSpeed = PlayerDefaults.MoveSpeed;
}

void URBPlayer::Act(URBGameSimulation* Simulation) {
    int Inputs = Simulation->_inputs[State.PlayerIndex];
    int MoveUp = Inputs & INPUT_MOVE_UP;
    int MoveDown = Inputs & INPUT_MOVE_DOWN;
    if (MoveUp) {
		State.Position.y = State.Position.y + State.MoveSpeed;
    }
    else if (MoveDown) {
		State.Position.y = State.Position.y - State.MoveSpeed;
    }
}

FSerializedEntity URBPlayer::SimSerialize() {
    FSerializedEntity result;
    result.EntityType = 0;
    result.Size = sizeof(State);
    memcpy(result.Bytes, &State, result.Size);
    return result;
}

void URBPlayer::SimDeserialize(FSerializedEntity SerializedEntity) {
    memcpy(&State, SerializedEntity.Bytes, SerializedEntity.Size);
}
