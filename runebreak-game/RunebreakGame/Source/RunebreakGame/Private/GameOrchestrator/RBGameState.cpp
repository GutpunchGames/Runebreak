#include "GameOrchestrator/RBGameState.h"
#include "GameOrchestrator/RBInput.h"

void GameState::Init()
{
    Position pos;
    pos.x = 0;
    pos.y = 0;
    Velocity vel;
    vel.dx = 0;
    vel.dy = 0;

    Player player1;
    player1.position = pos;
    player1.position.x = -100;
    player1.velocity = vel;
    _players[0] = player1;

    Player player2;
    player2.position = pos;
    player2.position.x = 100;
    player2.velocity = vel;
    _players[1] = player2;
}

void GameState::Update(int inputs[], int disconnect_flags)
{
    _framenumber++;
    int MoveUp = inputs[0] & INPUT_MOVE_UP;
    int MoveDown = inputs[0] & INPUT_MOVE_DOWN;
    if (MoveUp) {
		_players[0].position.y = _players[0].position.y + 10;
    }
    else if (MoveDown) {
		_players[0].position.y = _players[0].position.y - 10;
    }

    MoveUp = inputs[1] & INPUT_MOVE_UP;
    MoveDown = inputs[1] & INPUT_MOVE_DOWN;
    if (MoveUp) {
		_players[1].position.y = _players[1].position.y + 10;
    }
    else if (MoveDown) {
		_players[1].position.y = _players[1].position.y - 10;
    }
    UE_LOG(LogTemp, Warning, TEXT("GameState Update, frame: %d"), _framenumber)
}

