// Fill out your copyright notice in the Description page of Project Settings.


#include "Collisions/DetectionBoxActor.h"

void ADetectionBoxActor::SetDetectionBox(const FDetectionBox& DetectionBox) {
	Box = DetectionBox;
}

void ADetectionBoxActor::MarkInactive() {
	Box.Type = DetectionBoxType::Inactive;
}
