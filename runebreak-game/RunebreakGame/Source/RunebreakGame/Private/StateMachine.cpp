#include "StateMachine.h"

void UEntityState::TickState(USimulationEntity* Owner, URBGameSimulation* Simulation) {
	UE_LOG(LogTemp, Warning, TEXT("ticking state"))
	Frame++;
}

UEntityState* UEntityStateMachine::GetState() {
	return CurrentState;
}

void UEntityStateMachine::AddState(FString Name, UEntityState* State) {
	UE_LOG(LogTemp, Warning, TEXT("checkpoint 1"))
	UE_LOG(LogTemp, Warning, TEXT("setting state name: %s"), *Name)
	State->Name = Name;
	UE_LOG(LogTemp, Warning, TEXT("checkpoint 2"))
	UE_LOG(LogTemp, Warning, TEXT("states num: %d"), States.Num())
	States.Add(Name, State);
	UE_LOG(LogTemp, Warning, TEXT("checkpoint 3"))
	if (States.Num() == 1) {
		CurrentState = State;
	}
	UE_LOG(LogTemp, Warning, TEXT("checkpoint 4"))
}

void UEntityStateMachine::TransitionToState(UEntityState* State) {
	CurrentState = State;
}

void UEntityStateMachine::SkipToStateByName(const FString& StateName, int32 Frame) {
	SkipToState(States[StateName], Frame);
}

void UEntityStateMachine::SkipToState(UEntityState* State, int32 Frame) {
	CurrentState = State;
	CurrentState->Frame = Frame;
}

void UEntityStateMachine::TickState(USimulationEntity* Owner, URBGameSimulation* Simulation) {
	CurrentState->TickState(Owner, Simulation);
}
