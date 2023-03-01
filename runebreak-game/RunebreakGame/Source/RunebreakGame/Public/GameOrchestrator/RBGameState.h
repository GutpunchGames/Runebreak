// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

/*
 * Encapsulates all the game state for the Runebreak application inside
 * a single structure.  This makes it trivial to implement our GGPO
 * save and load functions.
 */

#define PI                    ((double)3.1415926)
#define STARTING_HEALTH       100
#define ROTATE_INCREMENT        3
#define SHIP_RADIUS            15
#define SHIP_WIDTH              8
#define SHIP_TUCK               3
#define SHIP_THRUST             0.06
#define SHIP_MAX_THRUST         4.0
#define SHIP_BREAK_SPEED        0.6
#define BULLET_SPEED            5
#define MAX_BULLETS             30
#define BULLET_COOLDOWN         8
#define BULLET_DAMAGE           10
#define GAME_WIDTH              640
#define GAME_HEIGHT             480

struct Position {
	double x, y;
};

struct Velocity {
	double dx, dy;
};

struct Player {
	Position position;
	Velocity velocity;
};

struct GameState {
	void Init(int num_players);
	void GetShipAI(int i, double* heading, double* thrust, int* fire);
	void ParseShipInputs(int inputs, int i, double* heading, double* thrust, int* fire);
	void MoveShip(int i, double heading, double thrust, int fire);
	void Update(int inputs[], int disconnect_flags);

public:
	int         _framenumber;
	Player      _players[2];
};
