#include "GameOrchestrator/RBPlayer.h"

void URBPlayer::Initialize(int32 PlayerIndex) {
    State.Position.x = PlayerIndex == 0 ? -100 : 100;
	State.PlayerIndex = PlayerIndex;

    // Add states
    StateMachine->AddState("Idle", NewObject<UPlayerState_Idle>(this));
}

void UPlayerState_Idle::TickState(USimulationEntity* Owner, URBGameSimulation* Simulation) {
    Super::TickState(Owner, Simulation);
    URBPlayer* Player = Cast<URBPlayer>(Owner);
    FRBPlayerState* State = &(Player->State);
    int Inputs = Simulation->_inputs[State->PlayerIndex];
    int MoveUp = Inputs & INPUT_MOVE_UP;
    int MoveDown = Inputs & INPUT_MOVE_DOWN;
    int Shoot = Inputs & INPUT_SHOOT;
    if (MoveUp) {
		State->Position.y = State->Position.y + State->MoveSpeed;
    }
    else if (MoveDown) {
		State->Position.y = State->Position.y - State->MoveSpeed;
    }

    if (Shoot) {
        if (State->FireballCooldown == 0) {
			Simulation->SpawnEntity(State->FireballPrototype);
            State->FireballCooldown = 60;
        }
    }

    if (State->FireballCooldown > 0) {
        State->FireballCooldown--;
    }
}

void URBPlayer::Act(URBGameSimulation* Simulation) {
    StateMachine->TickState(this, Simulation);
}

void URBPlayer::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Super::SerializeToBuffer(Serializer);
    Serializer->WriteBytes(&State, sizeof(State));
}

void URBPlayer::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Super::DeserializeFromBuffer(Deserializer);
    Deserializer->ReadBytes(&State, sizeof(State));
}
