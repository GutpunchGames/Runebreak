// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkMonitor.generated.h"

UCLASS(BlueprintType)
class UNetworkMonitor : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int AveragePing;

	void AddPing(int Ping);

private:
	int NumPingsCollected;
	TMap<FString, int> Pings;
	void ComputeStatistics();
};
