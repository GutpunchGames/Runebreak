// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameSimulation.h"

void UGameSimulation::AddLocalInput(FInput LocalInput) {
	UE_LOG(LogTemp, Warning, TEXT("Got Input: %s"), *LocalInput.ToString())
}

void UGameSimulation::AdvanceFrame() {
	FrameCount++;
}

void UGameSimulation::SerializeState() {

}
