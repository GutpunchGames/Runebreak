// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/RBGamePrimitivesBFL.h"

void URBGamePrimitivesBFL::ToTransform(const FPosition& Position, FTransform& Transform) {
	FVector Location;
	Location.Set(0, Position.x, Position.y);
	Transform.SetLocation(Location);
}
