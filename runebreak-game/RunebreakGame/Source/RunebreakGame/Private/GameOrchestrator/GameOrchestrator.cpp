#include "GameOrchestrator/GameOrchestrator.h"
#include "GGPOGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
AGameOrchestrator::AGameOrchestrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameOrchestrator::BeginPlay()
{
    Super::BeginPlay();

    UGGPONetwork* NetworkAddresses = nullptr;
    int32 NumPlayers = 1;

    // If this is a GGPO game instance
    UGameInstance* GameInstance = GetGameInstance();
    UGGPOGameInstance* GgpoGameInstance = Cast<UGGPOGameInstance>(GameInstance);
    if (GgpoGameInstance != nullptr)
    {
        // Get the network addresses
        NetworkAddresses = GgpoGameInstance->NetworkAddresses;
        NumPlayers = NetworkAddresses->NumPlayers();
        // Reset the game instance network addresses
        GgpoGameInstance->NetworkAddresses = nullptr;
    }

    bSessionStarted = TryStartGGPOPlayerSession(NumPlayers, NetworkAddresses);

    if (bSessionStarted)
    {
        OnSessionStarted();

        NetworkGraphData.Empty();
        TArray<FGGPONetworkStats> Network = GetNetworkStats();
        int32 Count = Network.Num();
        for (int32 i = 0; i < Count; i++)
        {
            NetworkGraphData.Add(FNetworkGraphPlayer{ });
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create GGPO session"));
    }
}

// Called every frame
void AGameOrchestrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<FGGPONetworkStats> AGameOrchestrator::GetNetworkStats()
{
    //GGPOPlayerHandle RemoteHandles[MAX_PLAYERS];
    //int Count = 0;
    //for (int i = 0; i < ngs.num_players; i++) {
    //    if (ngs.players[i].type == EGGPOPlayerType::REMOTE) {
    //        RemoteHandles[Count++] = ngs.players[i].handle;
    //    }
    //}

    TArray<FGGPONetworkStats> Result;
    //for (int i = 0; i < Count; i++)
    //{
    //    FGGPONetworkStats Stats = { 0 };
    //    GGPONet::ggpo_get_network_stats(ggpo, RemoteHandles[i], &Stats);
    //    Result.Add(Stats);
    //}

    return Result;
}

bool AGameOrchestrator::TryStartGGPOPlayerSession(
    int32 NumPlayers,
    const UGGPONetwork* NetworkAddresses)
{

    return false;

    //int32 Offset = 0;
    //GGPOPlayer Players[GGPO_MAX_SPECTATORS + GGPO_MAX_PLAYERS];
    //int32 NumSpectators = 0;

    //uint16 LocalPort;

    //// If there are no 
    //if (NetworkAddresses == nullptr)
    //{
    //    Players[0].size = sizeof(Players[0]);
    //    Players[0].player_num = 1;
    //    Players[0].type = EGGPOPlayerType::LOCAL;

    //    LocalPort = 7000;
    //    NumPlayers = 1;
    //}
    //else
    //{
    //    if (NumPlayers > NetworkAddresses->NumPlayers())
    //        return false;

    //    LocalPort = NetworkAddresses->GetLocalPort();

    //    int32 i;
    //    for (i = 0; i < NumPlayers; i++)
    //    {
    //        Offset++;

    //        Players[i].size = sizeof(Players[i]);
    //        Players[i].player_num = i + 1;
    //        // The local player
    //        if (i == NetworkAddresses->GetPlayerIndex()) {
    //            Players[i].type = EGGPOPlayerType::LOCAL;
    //            continue;
    //        }

    //        Players[i].type = EGGPOPlayerType::REMOTE;
    //        Players[i].u.remote.port = (uint16)NetworkAddresses->GetAddress(i)->GetPort();
    //        NetworkAddresses->GetAddress(i)->GetIpAddress(Players[i].u.remote.ip_address);
    //    }
    //    // these are spectators...
    //    while (Offset < NetworkAddresses->NumPlayers()) {
    //        Offset++;

    //        Players[i].type = EGGPOPlayerType::SPECTATOR;
    //        Players[i].u.remote.port = (uint16)NetworkAddresses->GetAddress(i)->GetPort();
    //        NetworkAddresses->GetAddress(i)->GetIpAddress(Players[i].u.remote.ip_address);

    //        i++;
    //        NumSpectators++;
    //    }
    //}

    //VectorWar_Init(LocalPort, NumPlayers, Players, NumSpectators);

    //UE_LOG(LogTemp, Display, TEXT("GGPO session started"));

    //return true;
}

void AGameOrchestrator::OnSessionStarted_Implementation() { }
