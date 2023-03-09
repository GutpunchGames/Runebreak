#include "GameOrchestrator/RBGameSimulation.h"
#include "GameOrchestrator/RBInput.h"

void FRBGameSimulation::Init()
{
    FPosition pos;
    pos.x = 0;
    pos.y = 0;
    FVelocity vel;
    vel.dx = 0;
    vel.dy = 0;

    FRBPlayer player1;
    player1.position = pos;
    player1.position.x = -100;
    player1.velocity = vel;
    player1.PlayerIndex = 0;
    _players[0] = player1;

    FRBPlayer player2;
    player2.position = pos;
    player2.position.x = 100;
    player2.velocity = vel;
    player2.PlayerIndex = 1;
    _players[1] = player2;
}

void FRBGameSimulation::Update(int inputs[], int disconnect_flags)
{
    _framenumber++;
    _inputs[0] = inputs[0];
    _inputs[1] = inputs[1];

    _players[0].SimulationTick(this);
    _players[1].SimulationTick(this);

    UE_LOG(LogTemp, Warning, TEXT("GameState Update, frame: %d"), _framenumber)
}

void FSimulationEntity::Serialize(void* OutState, int32* OutSize) {
}

void FSimulationEntity::SimulationTick(FRBGameSimulation* Simulation) { }

void FRBPlayer::SimulationTick(FRBGameSimulation* Simulation) {
    if (!Simulation) {
        UE_LOG(LogTemp, Warning, TEXT("BAD SIM"))
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Getting inputs for player: %d"), PlayerIndex)
    int Inputs = Simulation->_inputs[PlayerIndex];
    if (PlayerIndex == 1) {
        UE_LOG(LogTemp, Warning, TEXT("Got inputs: %d"), Inputs)
    }
    int MoveUp = Inputs & INPUT_MOVE_UP;
    int MoveDown = Inputs & INPUT_MOVE_DOWN;
    if (MoveUp) {
		position.y = position.y + 10;
    }
    else if (MoveDown) {
		position.y = position.y - 10;
    }
};
