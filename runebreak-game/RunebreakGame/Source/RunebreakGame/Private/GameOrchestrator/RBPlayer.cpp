#include "GameOrchestrator/RBPlayer.h"

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

void FRBPlayer::SimulationTick(FRBGameSimulation* Simulation) {
    if (!Simulation) {
        UE_LOG(LogTemp, Warning, TEXT("BAD SIM"))
        return;
    }
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
