#pragma once

#include "GameOrchestrator/RBGamePrimitives.h"
#include "GameOrchestrator/RBGameSerialization.h"
#include "GameOrchestrator/GameSimulationSerializer.h"
#include "GameOrchestrator/RBSimulationEntity.h"
#include "GameOrchestrator/RBGameSimulation.h"
#include "StateMachine.h"
#include "RBPlayer.generated.h"

UCLASS(Blueprintable)
class RUNEBREAKGAME_API UPlayerState_Idle : public UEntityState {
	GENERATED_BODY()

public:
	void TickState(USimulationEntity* Owner) override;

	UPROPERTY(EditAnywhere)
	UDataTable* FrameConfigs;
};

UCLASS(Blueprintable)
class RUNEBREAKGAME_API UPlayerState_Walk_Forward : public UEntityState {
	GENERATED_BODY()

public:
	void OnTransitionToState(UEntityState* Previous, USimulationEntity* Owner) override;
	void TickState(USimulationEntity* Owner) override;
};

UCLASS(Blueprintable)
class RUNEBREAKGAME_API UPlayerState_Walk_Back : public UEntityState {
	GENERATED_BODY()

public:
	void OnTransitionToState(UEntityState* Previous, USimulationEntity* Owner) override;
	void TickState(USimulationEntity* Owner) override;
};

UCLASS(Blueprintable)
class RUNEBREAKGAME_API UPlayerState_Punch : public UEntityState {
	GENERATED_BODY()

public:
	void TickState(USimulationEntity* Owner) override;
};

USTRUCT(BlueprintType)
struct FRBPlayerState {
	GENERATED_BODY()

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
		return PlayerIndex == Other.PlayerIndex
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
	virtual void ActivateDetectionBoxes(URBGameSimulation* Simulation) override;

	virtual void SetupStates(URBGameSimulation* Simulation) override;
	virtual void SerializeToBuffer(GameSimulationSerializer* Serializer);
	virtual void DeserializeFromBuffer(GameSimulationDeserializer* Deserializer) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRBPlayerState State;

	UFUNCTION(BlueprintCallable)
	void Initialize(int32 PlayerIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPlayerState_Idle> IdleStatePrototype;
};
