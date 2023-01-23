// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkMonitor.generated.h"

USTRUCT(BlueprintType)
struct FPingMessage {
	GENERATED_BODY()

public:
	long long OriginTimestamp;

	FString ToJson() {
		return FString::Printf(TEXT("{\"originTime\":\"%lld\"}"), OriginTimestamp);
	}
};

UCLASS(BlueprintType)
class UNetworkMonitor : public UObject {
	GENERATED_BODY()

public:
	UNetworkMonitor();
	~UNetworkMonitor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int AveragePing;

	void AddPing(int Ping);

	UFUNCTION()
	void DoPing();
	TFunction<void(long long CurrentTime)> PingImpl;

private:
	int NumPingsCollected;
	TMap<FString, int> Pings;
	void ComputeStatistics();
};
