#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "RBSimulationEntity.generated.h"

UCLASS(Blueprintable)
class UTestBlueprintEntity : public UObject {
	GENERATED_BODY()

public:
	int32 Id;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Test Blueprint Entity")
	void Method1();
	virtual void Method1_Implementation();
};

UCLASS()
class USimulationEntity : public UObject {
	GENERATED_BODY()

public:
	int32 Id;

	// todo: this should implement some interface instead of being a raw actor
	AActor* Actor = 0;

	virtual void SimulationTick(URBGameSimulation* Simulation);
	virtual FSerializedEntity Serialize();
	virtual void Deserialize(FSerializedEntity SerializedEntity);
};


