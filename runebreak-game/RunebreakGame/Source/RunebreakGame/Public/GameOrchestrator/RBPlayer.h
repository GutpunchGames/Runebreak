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
	int32 FireballCooldown = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveSpeed = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USimulationEntity> FireballPrototype;

	inline bool operator==(const FRBPlayerState& Other)
	{
		return Position.x == Other.Position.x
			&& Position.y == Other.Position.y
			&& PlayerIndex == Other.PlayerIndex
			&& MoveSpeed == Other.MoveSpeed
			&& FireballCooldown == Other.FireballCooldown;
	}
};

UCLASS(Blueprintable)
class URBPlayer : public USimulationEntity
{

GENERATED_BODY()

public:
	virtual void Act(URBGameSimulation* Simulation) override;
	virtual void SerializeToBuffer(unsigned char* buffer, int32* bytes_written) override;
	virtual void DeserializeFromBuffer(unsigned char* buffer, int32* bytes_read) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRBPlayerState State;

	UFUNCTION(BlueprintCallable)
	void Initialize(int32 PlayerIndex);
};
