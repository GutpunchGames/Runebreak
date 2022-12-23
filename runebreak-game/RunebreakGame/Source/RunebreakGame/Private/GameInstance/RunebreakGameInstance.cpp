// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RunebreakGameInstance.h"
#include <RunebreakGame/Public/TestObject/TestObject.h>

URunebreakGameInstance::URunebreakGameInstance() {
	// todo: should this be CreateDefaultSubobject? and what does the Name param do?
	api = NewObject<URunebreakAPI>(this, "Game Instance API");
}