#include "GameOrchestrator/GameSocket/NetworkStatistics.h"

FNetworkStatistics::FNetworkStatistics()
{
	AverageRoundTripTime = 0;
	PacketLoss = 0;
}

FNetworkStatistics::~FNetworkStatistics()
{
}
