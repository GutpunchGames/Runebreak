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

	UPROPERTY(BlueprintReadOnly)
	int MostRecentRemoteFrame;

	UPROPERTY(BlueprintReadOnly)
	// this is the most recently received ack from a remote client. thus we need to send
	// all inputs from this frame (plus one) up until our current frame.
	int MostRecentRemoteAck = -1;
};

