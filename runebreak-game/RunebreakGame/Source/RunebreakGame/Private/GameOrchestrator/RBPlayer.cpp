#include "GameOrchestrator/RBPlayer.h"
#include <RunebreakGame/Public/GameOrchestrator/RBInput.h>

URBPlayer::URBPlayer() {
}

void URBPlayer::Initialize(int32 PlayerIndex) {
    Position.x = PlayerIndex == 0 ? -100 : 100;
	State.PlayerIndex = PlayerIndex;
}

void URBPlayer::SetupStates(URBGameSimulation* Simulation) {
    Super::SetupStates(Simulation);

	UEntityState* IdleState = NewObject<UPlayerState_Idle>(this, FName("IdleState"));
    StateMachine->AddState("Idle", IdleState);

	UEntityState* WalkForwardState = NewObject<UPlayerState_Walk_Forward>(this, FName("WalkForwardState"));
    StateMachine->AddState("WalkForward", WalkForwardState);

	UEntityState* WalkBackState = NewObject<UPlayerState_Walk_Back>(this, FName("WalkBackState"));
    StateMachine->AddState("WalkBack", WalkBackState);
}

void UPlayerState_Idle::TickState(USimulationEntity* Owner) {
    Super::TickState(Owner);

    URBPlayer* Player = Cast<URBPlayer>(Owner);
    FRBPlayerState* State = &(Player->State);

    int Inputs = Simulation->_inputs[State->PlayerIndex];
    int MoveRight = Inputs & INPUT_MOVE_RIGHT;
    int MoveLeft = Inputs & INPUT_MOVE_LEFT;
    int Shoot = Inputs & INPUT_SHOOT;

    if (MoveRight) {
        Owner->StateMachine->TransitionToStateByName(this, "WalkForward", Owner);
        return;
    }
    else if (MoveLeft) {
        Owner->StateMachine->TransitionToStateByName(this, "WalkBack", Owner);
        return;
    }

    if (Shoot) {
        if (State->FireballCooldown == 0) {
			USimulationEntity* Fireball = Simulation->SpawnEntity(State->FireballPrototype);
            Fireball->Position = Owner->Position;
            State->FireballCooldown = 60;
        }
    }

    if (State->FireballCooldown > 0) {
        State->FireballCooldown--;
    }
}

void UPlayerState_Walk_Forward::OnTransitionToState(UEntityState* Previous, USimulationEntity* Owner) {
    Super::OnTransitionToState(Previous, Owner);
    URBPlayer* Player = Cast<URBPlayer>(Owner);
    FRBPlayerState* State = &(Player->State);

    Player->Move(State->MoveSpeed, 0);
}

void UPlayerState_Walk_Forward::TickState(USimulationEntity* Owner) {
    Super::TickState(Owner);
    URBPlayer* Player = Cast<URBPlayer>(Owner);
    FRBPlayerState* State = &(Player->State);
    int Inputs = Simulation->_inputs[State->PlayerIndex];
    int MoveRight = Inputs & INPUT_MOVE_RIGHT;
    int MoveLeft = Inputs & INPUT_MOVE_LEFT;

    if (MoveLeft) {
        Owner->StateMachine->TransitionToStateByName(this, "WalkBack", Owner);
        return;
    }
    else if (!MoveRight) {
        Owner->StateMachine->TransitionToStateByName(this, "Idle", Owner);
        return;
    }

	Player->Move(State->MoveSpeed, 0);

    FVector2D Size;
    Size.X = 100;
    Size.Y = 100;
    Simulation->ActivateDetectionBox(Owner->Id, Player->Position.x + 50, Player->Position.y + 100, 75, 100, DetectionBoxType::Collision);
}

void UPlayerState_Walk_Back::OnTransitionToState(UEntityState* Previous, USimulationEntity* Owner) {
    Super::OnTransitionToState(Previous, Owner);
    URBPlayer* Player = Cast<URBPlayer>(Owner);
    FRBPlayerState* State = &(Player->State);

    Player->Move(-1 * State->MoveSpeed, 0);
}

void UPlayerState_Walk_Back::TickState(USimulationEntity* Owner) {
    Super::TickState(Owner);
    URBPlayer* Player = Cast<URBPlayer>(Owner);
    FRBPlayerState* State = &(Player->State);

    int Inputs = Simulation->_inputs[State->PlayerIndex];
    int MoveRight = Inputs & INPUT_MOVE_RIGHT;
    int MoveLeft = Inputs & INPUT_MOVE_LEFT;
    if (MoveRight) {
        Owner->StateMachine->TransitionToStateByName(this, "WalkForward", Owner);
        return;
    }
    else if (!MoveLeft) {
        Owner->StateMachine->TransitionToStateByName(this, "Idle", Owner);
        return;
    }

	Player->Move(-1 * State->MoveSpeed, 0);
}

void URBPlayer::Act(URBGameSimulation* Simulation) {
    StateMachine->TickState(this);
}

void URBPlayer::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Super::SerializeToBuffer(Serializer);
    Serializer->WriteBytes(&State, sizeof(State));
}

void URBPlayer::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Super::DeserializeFromBuffer(Deserializer);
    Deserializer->ReadBytes(&State, sizeof(State));
}
