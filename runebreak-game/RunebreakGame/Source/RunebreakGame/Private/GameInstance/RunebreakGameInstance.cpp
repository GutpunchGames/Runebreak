// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RunebreakGameInstance.h"

URunebreakGameInstance::URunebreakGameInstance() {
	// todo: should this be CreateDefaultSubobject? and what does the Name param do?
	gameSession = NewObject<URBGameSession>(this, "Game Instance API");
}