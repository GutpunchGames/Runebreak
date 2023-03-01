#include "GameOrchestrator/RBGameState.h"

void GameState::Init(int num_players)
{
    Position pos;
    pos.x = 0;
    pos.y = 0;
    Velocity vel;
    vel.dx = 0;
    vel.dy = 0;

    Player player;
    player.position = pos;
    player.velocity = vel;
    _players[0] = player;
}

void GameState::GetShipAI(int i, double* heading, double* thrust, int* fire)
{
}

void GameState::ParseShipInputs(int inputs, int i, double* heading, double* thrust, int* fire)
{
}

void GameState::MoveShip(int which, double heading, double thrust, int fire)
{
}

void GameState::Update(int inputs[], int disconnect_flags)
{
    _framenumber++;
    _players[0].position.y = _players[0].position.y + 10;
    UE_LOG(LogTemp, Warning, TEXT("GameState Update, frame: %d"), _framenumber)
}

