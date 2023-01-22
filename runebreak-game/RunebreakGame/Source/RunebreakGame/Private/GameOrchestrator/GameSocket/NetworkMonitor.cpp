// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameSocket/NetworkMonitor.h"
#include <chrono>

void UNetworkMonitor::AddPing(int Ping) {
	// todo: add ping to Pings
	ComputeStatistics();
	FDateTime::Now();
}

void UNetworkMonitor::ComputeStatistics() {
	using namespace std::chrono;
	int ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	).count();
}
