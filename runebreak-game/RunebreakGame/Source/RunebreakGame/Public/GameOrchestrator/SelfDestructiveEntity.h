#pragma once

#include "CoreMinimal.h"
#include "GameOrchestrator/RBSimulationEntity.h"
#include "SelfDestructiveEntity.generated.h"

USTRUCT(BlueprintType)
struct FSelfDestructiveEntityState {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FPosition Position;
	UPROPERTY(BlueprintReadOnly)
	int32 MoveSpeed = 10;
	UPROPERTY(BlueprintReadOnly)
	int32 TimeAlive = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 TimeToLive;
};

USTRUCT(BlueprintType)
struct FSelfDestructiveEntityDefaults {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveSpeed = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TimeToLive = 100;
};

UCLASS(Blueprintable)
class RUNEBREAKGAME_API USelfDestructiveEntity : public USimulationEntity
{

GENERATED_BODY()

public:
	virtual void InitDefaults() override;
	virtual void Act(URBGameSimulation* Simulation) override;
	virtual FSerializedEntity SimSerialize() override;
	virtual void SimDeserialize(FSerializedEntity SerializedEntity) override;

	UPROPERTY(BlueprintReadOnly)
	FSelfDestructiveEntityState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSelfDestructiveEntityDefaults Defaults;
};
