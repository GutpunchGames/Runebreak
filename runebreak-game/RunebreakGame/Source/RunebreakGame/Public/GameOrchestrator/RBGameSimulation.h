#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBPlayer.h"
#include "GameOrchestrator/GameSimulationSerializer.h"
#include "RBGameSimulation.generated.h"


UCLASS()
class URBGameSimulation : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 _framenumber = 0;

	UPROPERTY()
	TMap<int32, USimulationEntity*> Entities;

	UPROPERTY()
	int32 _inputs[2];

	UFUNCTION(BlueprintCallable)
	USimulationEntity* SpawnEntity(UClass* EntityClassIN);

	UPROPERTY()
	int32 EntityIdGenerator = 0;

	bool RemoveEntity(int32 EntityId);

	void Init();
	void SimulationTick(int inputs[], int disconnect_flags);

	bool Save(unsigned char** buffer, int32* len, int32* checksum);
	bool Load(unsigned char* buffer, int32 len);

	void AddEntityToSimulation(USimulationEntity* Entity);

private:
	GameSimulationSerializer Serializer;
};
