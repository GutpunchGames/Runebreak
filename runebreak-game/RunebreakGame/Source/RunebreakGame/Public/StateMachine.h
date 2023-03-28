#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameOrchestrator/RBGamePrimitives.h"
#include "StateMachine.generated.h"

UCLASS(Blueprintable)
class RUNEBREAKGAME_API UEntityState : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	int32 Frame = 0;

	UPROPERTY(BlueprintReadOnly)
	URBGameSimulation* Simulation;

	UFUNCTION()
	virtual void BindToSimulation(URBGameSimulation* _Simulation);

	UFUNCTION()
	virtual void OnTransitionToState(UEntityState* Previous, USimulationEntity* Owner);

	UFUNCTION()
	virtual void OnEnterState();

	UFUNCTION()
	virtual void TickState(USimulationEntity* Owner);
};

UCLASS()
class RUNEBREAKGAME_API UEntityStateMachine : public UObject
{
	GENERATED_BODY()

protected:

public:

	UEntityStateMachine();

	UPROPERTY(VisibleAnywhere)
	URBGameSimulation* Simulation;

	UPROPERTY(VisibleAnywhere)
	TMap<FString, UEntityState*> States;

	UFUNCTION()
	void AddState(FString Name, UEntityState* State);

	UFUNCTION()
	UEntityState* GetState();

	UFUNCTION()
	void TransitionToState(UEntityState* Previous, UEntityState* Next, USimulationEntity* Owner);

	UFUNCTION()
	void TransitionToStateByName(UEntityState* Previous, const FString& StateName, USimulationEntity* Owner);

	UFUNCTION()
	void SkipToState(UEntityState* State, int32 Frame);

	UFUNCTION()
	void SkipToStateByName(const FString& StateName, int32 Frame = 0);

	UFUNCTION()
	void TickState(USimulationEntity* Owner);

	UPROPERTY()
	UEntityState* CurrentState = nullptr;
};
