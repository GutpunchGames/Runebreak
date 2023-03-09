#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBPlayer.h"
#include "RBGameSimulation.generated.h"

UCLASS()
class URBGameSimulation : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 _framenumber;
	UPROPERTY()
	int32 NumEntities;

	UPROPERTY()
	USimulationEntity* Entities[2];

	UPROPERTY()
	int32 _inputs[2];

	void Init();
	void Update(int inputs[], int disconnect_flags);
	URBPlayer* GetPlayer(int PlayerId);

	bool Save(unsigned char** buffer, int32* len, int32* checksum);
	bool Load(unsigned char* buffer, int32 len);
};
