// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/NetworkStatistics.h>
#include "NetworkMonitor.generated.h"

USTRUCT(BlueprintType)
struct FPingMessage {
	GENERATED_BODY()

public:
	UPROPERTY()
	FString OriginTimestamp;

	FString ToJson() {
		return FString::Printf(TEXT("{\"OriginTimestamp\":\"%s\"}"), *OriginTimestamp);
	}
};

USTRUCT(BlueprintType)
struct FPongMessage {
	GENERATED_BODY()

public:
	UPROPERTY()
	FString OriginTimestamp;

	FString ToJson() {
		return FString::Printf(TEXT("{\"OriginTimestamp\":\"%s\"}"), *OriginTimestamp);
	}
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNetworkStatisticsChanged, FNetworkStatistics);

UCLASS(BlueprintType)
class UNetworkMonitor : public UObject {
	GENERATED_BODY()

public:
	UNetworkMonitor();
	~UNetworkMonitor();

	void HandlePong(FPongMessage PongMessage);

	UFUNCTION()
	void DoPing();

	TFunction<void(FPingMessage)> PingImpl;

	FOnNetworkStatisticsChanged OnNetworkStatisticsChangedDelegate;

private:
	int PingIndex;
	int NumPingsTracked = 0;
	TArray<int> RoundTripTimes;

	FNetworkStatistics NetworkStatistics;
	void ComputeStatistics();
};
