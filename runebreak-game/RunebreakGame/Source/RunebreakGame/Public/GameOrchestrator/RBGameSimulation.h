#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/GameSimulationSerializer.h"
#include <RunebreakGame/Public/Collisions/DetectionBox.h>
#include "RBGameSimulation.generated.h"

static int32 MaxDetectionBoxes = 256;

UCLASS(Blueprintable)
class URBGameSimulation : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 _framenumber = 0;

	UPROPERTY()
	TMap<int32, USimulationEntity*> Entities;

	UPROPERTY()
	int32 _inputs[2];

	UFUNCTION(BlueprintCallable)
	USimulationEntity* SpawnEntity(UClass* EntityClassIN);

	UPROPERTY()
	int32 EntityIdGenerator = 0;

	UPROPERTY()
	int32 NumActiveDetectionBoxes;

	// this will be padded after each tick with inactive detection boxes. for size, refer to NumActiveDetectionBoxes.
	UPROPERTY(VisibleAnywhere)
	TArray<FDetectionBox> DetectionBoxes;

	bool RemoveEntity(int32 EntityId);

	void Init();
	void SimulationTick(int inputs[], int disconnect_flags);

	bool Save(unsigned char** buffer, int32* len, int32* checksum);
	bool Load(unsigned char* buffer, int32 len);

	void AddEntityToSimulation(USimulationEntity* Entity);
	void ActivateDetectionBox(int32 OwnerId, int32 PosX, int32 PosY, int32 SizeX, int32 SizeY, DetectionBoxType Type);

protected:

private:
	GameSimulationSerializer Serializer;
	GameSimulationDeserializer Deserializer;
};
