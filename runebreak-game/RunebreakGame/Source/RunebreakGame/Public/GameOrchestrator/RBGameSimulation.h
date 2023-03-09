#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBPlayer.h"
#include "RBGameSimulation.generated.h"

UCLASS()
class URBGameSimulation : public UObject {
	GENERATED_BODY()

public:
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
