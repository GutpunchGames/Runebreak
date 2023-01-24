// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkStatistics.generated.h"

USTRUCT(BlueprintType)
struct FNetworkStatistics {
	GENERATED_BODY()

public:
	FNetworkStatistics();
	~FNetworkStatistics();

	UPROPERTY(BlueprintReadOnly)
		float AverageRoundTripTime;

	UPROPERTY(BlueprintReadOnly)
		float PacketLoss;
};

