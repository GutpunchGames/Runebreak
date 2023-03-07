// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

/*
 * Encapsulates all the game state for the Runebreak application inside
 * a single structure.  This makes it trivial to implement our GGPO
 * save and load functions.
 */

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

struct RBGameSimulation {
	void Init();
	void Update(int inputs[], int disconnect_flags);

public:
	int         _framenumber;
	Player      _players[2];
};
