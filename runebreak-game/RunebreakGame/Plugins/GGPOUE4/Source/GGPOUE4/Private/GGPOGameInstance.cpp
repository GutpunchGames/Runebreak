// Copyright 2020 BwdYeti.


#include "GGPOGameInstance.h"
#include "include/ggponet.h"

void UGGPOGameInstance::CreateNetwork(int32 PlayerIndex, int32 LocalPort, FString RemoteAddress)
{
	TArray<FString> RemoteAddresses;
	if (!RemoteAddress.IsEmpty()) {
		RemoteAddresses.Add(RemoteAddress);
	}

	UGGPONetwork* addresses = UGGPONetwork::CreateNetwork(
		this,
		FName(FString(TEXT("GGPONetwork"))),
		2,
		PlayerIndex,
		LocalPort,
		RemoteAddresses);

	NetworkAddresses = addresses;
}

