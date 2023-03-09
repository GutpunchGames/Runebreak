#include "GameOrchestrator/RBPlayer.h"

void FRBPlayer::SimulationTick(FRBGameSimulation* Simulation) {
    int Inputs = Simulation->_inputs[PlayerIndex];
    int MoveUp = Inputs & INPUT_MOVE_UP;
    int MoveDown = Inputs & INPUT_MOVE_DOWN;
    if (MoveUp) {
		position.y = position.y + 10;
    }
    else if (MoveDown) {
		position.y = position.y - 10;
    }
};

FSerializedEntity FRBPlayer::Serialize() {
    FSerializedEntity result;
    result.EntityType = 0;
    result.Size = sizeof(*this);
    memcpy(result.Bytes, this, result.Size);
    return result;
}

void FRBPlayer::Deserialize(FSerializedEntity SerializedEntity) {
    memcpy(this, SerializedEntity.Bytes, SerializedEntity.Size);
}
