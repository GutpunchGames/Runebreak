#include "StateMachine.h"

UEntityStateMachine::UEntityStateMachine() {
}

void OnStateEnter(USimulationEntity* Owner) {

}

void UEntityState::BindToSimulation(URBGameSimulation* _Simulation) {
	Simulation = _Simulation;
	Frame++;
}

void UEntityState::TickState(USimulationEntity* Owner) {
	Frame++;
}

UEntityState* UEntityStateMachine::GetState() {
	return CurrentState;
}

void UEntityState::OnTransitionToState(UEntityState* Previous, USimulationEntity* Owner) { }

void UEntityState::OnEnterState() { }

void UEntityStateMachine::AddState(FString Name, UEntityState* State) {
	State->Name = Name;
	State->BindToSimulation(Simulation);
	States.Add(Name, State);
	if (!CurrentState) {
		CurrentState = State;
	}
}

void UEntityStateMachine::TransitionToState(UEntityState* Previous, UEntityState* Next, USimulationEntity* Owner) {
	CurrentState = Next;
	CurrentState->Frame = 1;
	CurrentState->OnEnterState();
	CurrentState->OnTransitionToState(Previous, Owner);
}

void UEntityStateMachine::TransitionToStateByName(UEntityState* Previous, const FString& StateName, USimulationEntity* Owner) {
	TransitionToState(Previous, States[StateName], Owner);
}

void UEntityStateMachine::SkipToState(UEntityState* State, int32 Frame) {
	CurrentState = State;
	CurrentState->Frame = Frame;
	CurrentState->OnEnterState();
}

void UEntityStateMachine::SkipToStateByName(const FString& StateName, int32 Frame) {
	SkipToState(States[StateName], Frame);
}

void UEntityStateMachine::TickState(USimulationEntity* Owner) {
	CurrentState->TickState(Owner);
}
