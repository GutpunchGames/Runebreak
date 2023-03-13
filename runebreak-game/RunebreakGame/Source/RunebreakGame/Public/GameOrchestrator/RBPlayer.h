#pragma once

#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "GameOrchestrator/RBSimulationEntity.h"
#include "RBPlayer.generated.h"

USTRUCT(BlueprintType)
struct FRBPlayerState {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FPosition Position;
	UPROPERTY(BlueprintReadOnly)
	int32 PlayerIndex;
	UPROPERTY(BlueprintReadOnly)
	int32 MoveSpeed;
};

USTRUCT(BlueprintType)
struct FRBPlayerDefaults {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveSpeed = 10;
};

UCLASS(Blueprintable)
class URBPlayer : public USimulationEntity {

GENERATED_BODY()

public:
	virtual void Act(URBGameSimulation* Simulation) override;
	virtual FSerializedEntity Serialize() override;
	virtual void Deserialize(FSerializedEntity SerializedEntity) override;

	UPROPERTY(BlueprintReadOnly)
	FRBPlayerState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRBPlayerDefaults PlayerDefaults;

	UFUNCTION(BlueprintCallable)
	void Initialize(int32 PlayerIndex);
};
