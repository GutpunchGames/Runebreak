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
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<USimulationEntity> FireballPrototype;

	inline bool operator==(const FRBPlayerState& Other)
	{
		return Position.x == Other.Position.x
			&& Position.y == Other.Position.y
			&& PlayerIndex == Other.PlayerIndex
			&& MoveSpeed == Other.MoveSpeed;
	}
};

USTRUCT(BlueprintType)
struct FRBPlayerDefaults {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveSpeed = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USimulationEntity> FireballPrototype;
};

UCLASS(Blueprintable)
class URBPlayer : public USimulationEntity
{

GENERATED_BODY()

public:
	virtual void Act(URBGameSimulation* Simulation) override;
	virtual void* GetState(int32& SizeOUT) override;

	UPROPERTY(BlueprintReadOnly)
	FRBPlayerState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRBPlayerDefaults PlayerDefaults;

	UFUNCTION(BlueprintCallable)
	void Initialize(int32 PlayerIndex);
};
