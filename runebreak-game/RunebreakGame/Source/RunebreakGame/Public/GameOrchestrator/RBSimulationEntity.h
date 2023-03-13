#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "GameOrchestrator/SimulationActor.h"
#include "RBSimulationEntity.generated.h"

UCLASS()
class USimulationEntity : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Id;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASimulationActor> ActorClass;

	virtual void InitDefaults();
	virtual void Act(URBGameSimulation* Simulation);
	virtual void ResolveCollisions(URBGameSimulation* Simulation);
	virtual FSerializedEntity Serialize();
	virtual void Deserialize(FSerializedEntity SerializedEntity);
};


