#pragma once

#include "GameOrchestrator/RBPlayer.h"

struct FRBGameSimulation {
	int	_framenumber;
	int NumEntities;
	FSimulationEntity* Entities[2];
	int32 _inputs[2];

	void Init();
	void Update(int inputs[], int disconnect_flags);
	FRBPlayer* GetPlayer(int PlayerId);

	bool Save(unsigned char** buffer, int32* len, int32* checksum);
	bool Load(unsigned char* buffer, int32 len);
};
