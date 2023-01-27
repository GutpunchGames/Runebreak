// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/NetworkStatistics.h>
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/GameSocketMessages.h>
#include "NetworkMonitor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNetworkStatisticsChanged, FNetworkStatistics);

UCLASS(BlueprintType)
class UNetworkMonitor : public UObject {
	GENERATED_BODY()

public:
	UNetworkMonitor();
	~UNetworkMonitor();

	void HandlePong(FPongMessage PongMessage);

	UPROPERTY()
	int MostRecentRemoteFrame;

	UPROPERTY()
	FNetworkStatistics NetworkStatistics;

	FOnNetworkStatisticsChanged OnNetworkStatisticsChangedDelegate;

private:
	UPROPERTY()
	int PingIndex;

	UPROPERTY()
	int NumPingsTracked = 0;

	UPROPERTY()
	TArray<int> RoundTripTimes;

	void ComputeStatistics(int RemoteFrame);
};
