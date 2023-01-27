#include "GameOrchestrator/GameSocket/NetworkStatistics.h"

FNetworkStatistics::FNetworkStatistics()
{
	AverageRoundTripTime = 0;
	PacketLoss = 0;
	MostRecentRemoteFrame = -1;
}

FNetworkStatistics::~FNetworkStatistics()
{
}
