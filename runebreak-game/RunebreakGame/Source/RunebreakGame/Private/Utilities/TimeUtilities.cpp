// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/TimeUtilities.h"
#include <chrono>

// returns the millis since the unix epoch
int64 TimeUtilities::GetMillisSinceEpoch() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
}

