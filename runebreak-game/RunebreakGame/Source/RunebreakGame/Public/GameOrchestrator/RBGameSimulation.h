#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBPlayer.h"
#include "RBGameSimulation.generated.h"

UCLASS()
class URBGameSimulation : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 _framenumber = 0;

	UPROPERTY()
	TArray<USimulationEntity*> Entities;

	UPROPERTY()
	int32 _inputs[2];

	UFUNCTION(BlueprintCallable)
	int32 SpawnEntity(int32 EntityType, int DebugPlayerIndex);

	void Init();
	void Update(int inputs[], int disconnect_flags);
	URBPlayer* GetPlayer(int PlayerId);

	bool Save(unsigned char** buffer, int32* len, int32* checksum);
	bool Load(unsigned char* buffer, int32 len);

private:
	UPROPERTY()
	int32 EntityIdGenerator;

	UPROPERTY()
	int32 NumEntities;
};
