#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "GameOrchestrator/GameSimulationSerializer.h"
#include "StateMachine.h"
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

	UPROPERTY(BlueprintReadOnly)
	UEntityStateMachine* StateMachine;

	virtual void SetupStates();
	virtual void InitDefaults();
	virtual void Act(URBGameSimulation* Simulation);
	virtual void ResolveCollisions(URBGameSimulation* Simulation);

	virtual void SerializeToBuffer(GameSimulationSerializer* Serializer);
	virtual void DeserializeFromBuffer(GameSimulationDeserializer* Deserializer);
};


