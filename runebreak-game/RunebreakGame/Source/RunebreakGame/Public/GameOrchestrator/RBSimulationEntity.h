#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "RBSimulationEntity.generated.h"

UCLASS()
class USimulationEntity : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Id;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASimulationActor> ActorClass;

	UPROPERTY()
	TSubclassOf<USimulationEntity> EntityClass;

	virtual void InitDefaults();
	virtual void Act(URBGameSimulation* Simulation);
	virtual void ResolveCollisions(URBGameSimulation* Simulation);
	virtual void* GetState(int32& SizeOUT);
	FSerializedEntity SimSerialize();
	void SimDeserialize(const FSerializedEntity& SerializedEntity);
};


