// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameSocket/NetworkMonitor.h"
#include <chrono>

UNetworkMonitor::UNetworkMonitor() {

}

UNetworkMonitor::~UNetworkMonitor() {

}

void UNetworkMonitor::AddPing(int Ping) {
	// todo: add ping to Pings
	ComputeStatistics();
}

void UNetworkMonitor::ComputeStatistics() {
}

void UNetworkMonitor::DoPing() {
	long long CurrentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		).count();

	PingImpl(CurrentTime);
}
