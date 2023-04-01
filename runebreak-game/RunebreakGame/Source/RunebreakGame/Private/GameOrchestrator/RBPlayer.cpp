#include "GameOrchestrator/RBPlayer.h"
#include <RunebreakGame/Public/GameOrchestrator/RBInput.h>

URBPlayer::URBPlayer() {
}

void URBPlayer::Initialize(int32 PlayerIndex) {
    Position.x = PlayerIndex == 0 ? -100 : 100;
	State.PlayerIndex = PlayerIndex;
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

    int Punch = Inputs & INPUT_LIGHT_ATTACK;

    if (Punch) {
        Owner->StateMachine->TransitionToStateByName(this, "Punch", Owner);
        return;
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

void UPlayerState_Punch::TickState(USimulationEntity* Owner) {
    Super::TickState(Owner);

    if (Frame >= 60) {
        Owner->StateMachine->TransitionToStateByName(this, "Idle", Owner);
        return;
    }
}

void URBPlayer::Act(URBGameSimulation* Simulation) {
    StateMachine->TickState(this);
}

void URBPlayer::ActivateDetectionBoxes(URBGameSimulation* Simulation) {
  //  if (StateMachine->CurrentState->Name.Equals("Idle")) {
  //      UPlayerState_Idle* IdleState = Cast<UPlayerState_Idle>(StateMachine->CurrentState);
  //      int NumRows = IdleState->FrameConfigs->GetRowNames().Num();

  //      // this makes the hitboxes loop, do something about this later
  //      int RowKeyInt = (IdleState->Frame % NumRows) + 1;
		//FString RowKey = FString::Printf(TEXT("%d"), RowKeyInt);
  //      FStateFrame* Config = IdleState->FrameConfigs->FindRow<FStateFrame>(*RowKey, "");
  //      if (Config) {
		//	for (int i = 0; i < Config->Boxes.Num(); i++) {
		//		FDetectionBoxConfig BoxConfig = Config->Boxes[i];
		//		Simulation->ActivateDetectionBox(Id, Position.x + BoxConfig.Offset.X, Position.y + BoxConfig.Offset.Y, BoxConfig.Size.X, BoxConfig.Size.Y, BoxConfig.Type);
		//	}
  //      }
  //      else {
  //          UE_LOG(LogTemp, Warning, TEXT("Failed to find config for frame: %d"), IdleState->Frame)
  //      }
  //  }
}

void URBPlayer::SerializeToBuffer(GameSimulationSerializer* Serializer) {
    Super::SerializeToBuffer(Serializer);
    Serializer->WriteBytes(&State, sizeof(State));
}

void URBPlayer::DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) {
    Super::DeserializeFromBuffer(Deserializer);
    Deserializer->ReadBytes(&State, sizeof(State));
}
