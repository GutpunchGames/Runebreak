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

	UFUNCTION()
	virtual void TickState(USimulationEntity* Owner, URBGameSimulation* Simulation);
};

UCLASS()
class RUNEBREAKGAME_API UEntityStateMachine : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UEntityState* CurrentState = nullptr;

public:

	UEntityStateMachine();

	UFUNCTION()
	void AddState(FString Name, UEntityState* State);

	UPROPERTY(VisibleAnywhere)
	TMap<FString, UEntityState*> States;

	UFUNCTION()
	UEntityState* GetState();

	UFUNCTION()
	void TransitionToState(UEntityState* State);

	UFUNCTION()
	void SkipToStateByName(const FString& StateName, int32 Frame);

	UFUNCTION()
	void SkipToState(UEntityState* State, int32 Frame);

	UFUNCTION()
	void TickState(USimulationEntity* Owner, URBGameSimulation* Simulation);
};
