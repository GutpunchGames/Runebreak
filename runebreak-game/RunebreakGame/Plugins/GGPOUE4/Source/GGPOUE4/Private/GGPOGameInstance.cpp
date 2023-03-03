// Copyright 2020 BwdYeti.


#include "GGPOGameInstance.h"
#include "include/ggponet.h"

void UGGPOGameInstance::CreateNetwork(TSet<int32> LocalPlayerIndices, int32 LocalPort, FString RemoteAddress)
{
	TArray<FString> RemoteAddresses;
	if (!RemoteAddress.IsEmpty()) {
		RemoteAddresses.Add(RemoteAddress);
	}

	UGGPONetwork* addresses = UGGPONetwork::CreateNetwork(
		this,
		FName(FString(TEXT("GGPONetwork"))),
		2,
		LocalPlayerIndices,
		LocalPort,
		RemoteAddresses);

	UE_LOG(LogTemp, Warning, TEXT("Created network with num players: %d"), addresses->NumPlayers())
	GGPONetwork = addresses;
}

