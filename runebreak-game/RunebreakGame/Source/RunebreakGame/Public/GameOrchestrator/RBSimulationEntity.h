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

	UPROPERTY(BlueprintReadOnly)
	FPosition Position;

	virtual void SetupStates(URBGameSimulation* Simulation);
	virtual void InitDefaults();
	virtual void ResolveCollisions(URBGameSimulation* Simulation);

	void SimulationTick(URBGameSimulation* Simulation);

	virtual void SerializeToBuffer(GameSimulationSerializer* Serializer);
	virtual void DeserializeFromBuffer(GameSimulationDeserializer* Deserializer);

	virtual void Move(const int32& X, const int32& Y);

protected:
	virtual void Act(URBGameSimulation* Simulation);
	virtual void ActivateDetectionBoxes(URBGameSimulation* Simulation);
};

