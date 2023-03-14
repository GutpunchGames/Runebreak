#include "GameOrchestrator/RBPlayer.h"

void URBPlayer::Initialize(int32 PlayerIndex) {
    State.Position.x = PlayerIndex == 0 ? -100 : 100;
	State.PlayerIndex = PlayerIndex;
	State.MoveSpeed = PlayerDefaults.MoveSpeed;
    State.FireballPrototype = PlayerDefaults.FireballPrototype;
    State.FireballCooldown = 0;
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
        if (State.FireballCooldown == 0) {
            UE_LOG(LogTemp, Warning, TEXT("Spawned Fireball"))
			Simulation->SpawnEntity(State.FireballPrototype);
            State.FireballCooldown = 60;
        }
    }

    if (State.FireballCooldown > 0) {
        State.FireballCooldown--;
    }
}

void URBPlayer::SerializeToBuffer(unsigned char* buffer, int32* bytes_written) {
    Super::SerializeToBuffer(buffer, bytes_written);
    memcpy(buffer + *bytes_written, &State, sizeof(State));
    *(bytes_written) += sizeof(State);
}

void URBPlayer::DeserializeFromBuffer(unsigned char* buffer, int32* bytes_read) {
    Super::DeserializeFromBuffer(buffer, bytes_read);
    memcpy(&State, buffer + *bytes_read, sizeof(State));
    *(bytes_read) += sizeof(State);
}
