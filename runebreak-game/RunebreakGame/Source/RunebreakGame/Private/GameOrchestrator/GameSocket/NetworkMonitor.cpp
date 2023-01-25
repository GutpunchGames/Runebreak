// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameSocket/NetworkMonitor.h"
#include "Misc/DefaultValueHelper.h"
#include <Utilities/TimeUtilities.h>
#include <chrono>

UNetworkMonitor::UNetworkMonitor() {
	RoundTripTimes.SetNumUninitialized(3);
	PingIndex = 0;
}

UNetworkMonitor::~UNetworkMonitor() {

}

void UNetworkMonitor::HandlePong(FPongMessage PongMessage) {
	UE_LOG(LogTemp, Warning, TEXT("HandlePong: %d"), *PongMessage.OriginTimestamp)

	int64 CurrentTime = TimeUtilities::GetMillisSinceEpoch();
	int64 OriginTime;
	FDefaultValueHelper::ParseInt64(PongMessage.OriginTimestamp, OriginTime);
	int RoundTripTime = (CurrentTime - OriginTime);

	RoundTripTimes[PingIndex] = RoundTripTime;

	// increment NumPingsTracked, but keep it at or under the max index in RoundTripTimes
	NumPingsTracked = FMath::Min(NumPingsTracked + 1, RoundTripTimes.Num() - 1);

	// increment PingIndex (which tracks which ping we're going to overwrite next)
	PingIndex++;
	if (PingIndex == RoundTripTimes.Num()) {
		PingIndex = 0;
	}

	ComputeStatistics();
}

void UNetworkMonitor::ComputeStatistics() {
	int Total = 0;
	for (int i = 0; i < NumPingsTracked; i++) {
		Total += RoundTripTimes[i];
	}

	NetworkStatistics.AverageRoundTripTime = (float)Total / (float) RoundTripTimes.Num();
	UE_LOG(LogTemp, Warning, TEXT("Computed ping: %f"), NetworkStatistics.AverageRoundTripTime);
	NetworkStatistics.PacketLoss = -1;
	OnNetworkStatisticsChangedDelegate.Broadcast(NetworkStatistics);
}

void UNetworkMonitor::DoPing() {
	int64 CurrentTime = TimeUtilities::GetMillisSinceEpoch();

	FPingMessage Message;
	Message.OriginTimestamp = FString::Printf(TEXT("%lld"), CurrentTime);

	PingImpl(Message);
}
