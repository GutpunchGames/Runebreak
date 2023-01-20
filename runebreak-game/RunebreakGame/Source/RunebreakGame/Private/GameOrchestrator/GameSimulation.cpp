// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameSimulation.h"

void UGameSimulation::AddLocalInput(int MoveDirection) {
	// todo: handle this
}

void UGameSimulation::AdvanceFrame() {
	FrameCount++;
}

void UGameSimulation::SerializeState() {

}

int UGameSimulation::GetFrameCount() {
	return FrameCount;
}
