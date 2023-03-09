#pragma once

#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "GameOrchestrator/RBSimulationEntity.h"
#include "RBPlayer.generated.h"

USTRUCT()
struct FRBPlayerState {
	GENERATED_BODY()

	UPROPERTY()
	FPosition Position;
	UPROPERTY()
	int32 PlayerIndex;
};

UCLASS()
class URBPlayer : public USimulationEntity {

GENERATED_BODY()

public:
	void Initialize(FPosition Position, int32 PlayerIndex);
	virtual void SimulationTick(URBGameSimulation* Simulation) override;
	virtual FSerializedEntity Serialize() override;
	virtual void Deserialize(FSerializedEntity SerializedEntity) override;

	UPROPERTY()
	FRBPlayerState State;
};
