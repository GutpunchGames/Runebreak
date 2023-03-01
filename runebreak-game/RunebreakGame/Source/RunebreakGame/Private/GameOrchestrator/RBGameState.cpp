#include "GameOrchestrator/RBInput.h"
#include "GameOrchestrator/RBGameState.h"

void GameState::Init()
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
    UE_LOG(LogTemp, Warning, TEXT("GameState Update, frame: %d"), _framenumber)
}

