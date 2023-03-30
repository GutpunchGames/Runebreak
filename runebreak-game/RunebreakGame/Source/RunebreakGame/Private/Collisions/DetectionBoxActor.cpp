// Fill out your copyright notice in the Description page of Project Settings.


#include "Collisions/DetectionBoxActor.h"

void ADetectionBoxActor::SetDetectionBox(const FDetectionBox& DetectionBox) {
	UE_LOG(LogTemp, Warning, TEXT("Set detection box with type: %d -- position: %f, %f -- size: %f, %f"), (uint8)DetectionBox.Type, DetectionBox.Position.x, DetectionBox.Position.y, DetectionBox.Size.X, DetectionBox.Size.Y)
	Box = DetectionBox;
}

void ADetectionBoxActor::MarkInactive() {
	Box.Type = DetectionBoxType::Inactive;
}
