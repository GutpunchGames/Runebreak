#include "StateMachine.h"

UEntityStateMachine::UEntityStateMachine() {
}

void UEntityState::TickState(USimulationEntity* Owner, URBGameSimulation* Simulation) {
	UE_LOG(LogTemp, Warning, TEXT("ticking state"))
	Frame++;
}

UEntityState* UEntityStateMachine::GetState() {
	return CurrentState;
}

void UEntityStateMachine::AddState(FString Name, UEntityState* State) {
	State->Name = Name;
	States.Add(Name, State);
	if (!CurrentState) {
		CurrentState = State;
	}
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
