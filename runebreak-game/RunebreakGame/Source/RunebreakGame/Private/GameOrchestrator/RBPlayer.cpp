#include "GameOrchestrator/RBPlayer.h"

void URBPlayer::Initialize(int32 PlayerIndex) {
    State.Position.x = PlayerIndex == 0 ? -100 : 100;
	State.PlayerIndex = PlayerIndex;
	State.MoveSpeed = PlayerDefaults.MoveSpeed;
    State.FireballPrototype = PlayerDefaults.FireballPrototype;
}

void URBPlayer::Act(URBGameSimulation* Simulation) {
    int Inputs = Simulation->_inputs[State.PlayerIndex];
    int MoveUp = Inputs & INPUT_MOVE_UP;
    int MoveDown = Inputs & INPUT_MOVE_DOWN;
    int Shoot = Inputs & INPUT_SHOOT;
    if (MoveUp) {
		State.Position.y = State.Position.y + State.MoveSpeed;
    }
    else if (MoveDown) {
		State.Position.y = State.Position.y - State.MoveSpeed;
    }

    if (Shoot) {
       UE_LOG(LogTemp, Warning, TEXT("Spawned Fireball"))
       Simulation->SpawnEntity(State.FireballPrototype);
    }
}

void* URBPlayer::GetState(int32& SizeOUT) {
    SizeOUT = sizeof(State);
    return &State;
}
