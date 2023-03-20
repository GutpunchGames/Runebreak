#pragma once

#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "GameOrchestrator/GameSimulationSerializer.h"
#include "GameOrchestrator/RBSimulationEntity.h"
#include "RBPlayer.generated.h"

UCLASS(Blueprintable)
class RUNEBREAKGAME_API UPlayerState_Idle : public UEntityState {
	GENERATED_BODY()

public:
	virtual void TickState(USimulationEntity* Owner, URBGameSimulation* Simulation) override;
};

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
	URBPlayer();

	virtual void Act(URBGameSimulation* Simulation) override;

	virtual void SerializeToBuffer(GameSimulationSerializer* Serializer);
	virtual void DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRBPlayerState State;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerState_Idle> IdleState;

	UFUNCTION(BlueprintCallable)
	void Initialize(int32 PlayerIndex);
};
