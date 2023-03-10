#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "RBSimulationEntity.generated.h"

UCLASS()
class USimulationEntity : public UObject {
	GENERATED_BODY()

public:
	int32 Id;

	virtual void SimulationTick(URBGameSimulation* Simulation);
	virtual FSerializedEntity Serialize();
	virtual void Deserialize(FSerializedEntity SerializedEntity);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Test Blueprint Entity")
	void Method1();
	virtual void Method1_Implementation();
};


