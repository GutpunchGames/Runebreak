#include "GameOrchestrator/GGPOGameOrchestrator.h"
#include "GameOrchestrator/RBPlayerController.h"
#include "GameOrchestrator/Checksum.h"
#include "GGPOGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// UE4: allow Windows platform types to avoid naming collisions
//  this must be undone at the bottom of this file
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <timeapi.h>

#define FRAME_DELAY 0
#define FRAME_RATE 60
#define ONE_FRAME (1.0f / FRAME_RATE)

// Sets default values
AGGPOGameOrchestrator::AGGPOGameOrchestrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGGPOGameOrchestrator::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay"))

    UGGPONetwork* GGPONetwork = nullptr;
    int32 NumPlayers = 2;

    // If this is a GGPO game instance
    UGameInstance* GameInstance = GetGameInstance();
    UGGPOGameInstance* GgpoGameInstance = Cast<UGGPOGameInstance>(GameInstance);
    if (GgpoGameInstance != nullptr)
    {
        // Get the network addresses
        GGPONetwork = GgpoGameInstance->GGPONetwork;
        NumPlayers = GGPONetwork->NumPlayers();
        // Reset the game instance network addresses
        GgpoGameInstance->GGPONetwork = nullptr;
    }

    UE_LOG(LogTemp, Warning, TEXT("got num players: %d"), NumPlayers)
    bSessionStarted = TryStartGGPOSession(NumPlayers, GGPONetwork);

    UE_LOG(LogTemp, Warning, TEXT("Session Started: %b"), bSessionStarted)

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
void AGGPOGameOrchestrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    ElapsedTime += DeltaTime;

    int32 IdleMs = (int32)(ONE_FRAME - (int32)(ElapsedTime * 1000));
    Idle(FMath::Max(0, IdleMs - 1));
    while (ElapsedTime >= ONE_FRAME) {
        TickGameState();
        ElapsedTime -= ONE_FRAME;
    }
}

TArray<FGGPONetworkStats> AGGPOGameOrchestrator::GetNetworkStats()
{
    GGPOPlayerHandle RemoteHandles[MAX_PLAYERS];
    int Count = 0;
    for (int i = 0; i < ngs.num_players; i++) {
        if (ngs.players[i].type == EGGPOPlayerType::REMOTE) {
            RemoteHandles[Count++] = ngs.players[i].handle;
        }
    }

    TArray<FGGPONetworkStats> Result;
    for (int i = 0; i < Count; i++)
    {
        FGGPONetworkStats Stats = { 0 };
        GGPONet::ggpo_get_network_stats(ggpo, RemoteHandles[i], &Stats);
        Result.Add(Stats);
    }

    return Result;
}

bool AGGPOGameOrchestrator::TryStartGGPOSession(
    int32 NumPlayers,
    const UGGPONetwork* NetworkAddresses)
{
    GGPOPlayer Players[GGPO_MAX_SPECTATORS + GGPO_MAX_PLAYERS];
    uint16 LocalPort;

    // If there are no network addresses...
    if (NetworkAddresses == nullptr)
    {
        Players[0].size = sizeof(Players[0]);
        Players[0].player_num = 1;
        Players[0].type = EGGPOPlayerType::LOCAL;

        Players[1].size = sizeof(Players[0]);
        Players[1].player_num = 2;
        Players[1].type = EGGPOPlayerType::LOCAL;

        LocalPort = 7000;
        NumPlayers = 2;
    }
    else
    {
        if (NumPlayers > NetworkAddresses->NumPlayers())
            return false;

        LocalPort = NetworkAddresses->GetLocalPort();

        int32 i;
        for (i = 0; i < NumPlayers; i++)
        {
            Players[i].size = sizeof(Players[i]);
            Players[i].player_num = i + 1;
            // The local player
            if (NetworkAddresses->IsPlayerLocal(i)) {
                Players[i].type = EGGPOPlayerType::LOCAL;
            }
            else {
                Players[i].type = EGGPOPlayerType::REMOTE;
                Players[i].u.remote.port = (uint16)NetworkAddresses->GetAddress(i)->GetPort();
                NetworkAddresses->GetAddress(i)->GetIpAddress(Players[i].u.remote.ip_address);
            }
        }
    }

    ConfigureGGPO(LocalPort, NumPlayers, Players);

    UE_LOG(LogTemp, Display, TEXT("GGPO session started"));

    return true;
}

void AGGPOGameOrchestrator::OnSessionStarted_Implementation() { 
}

void AGGPOGameOrchestrator::ConfigureGGPO(uint16 localport, int32 num_players, GGPOPlayer* players)
{
    GGPOErrorCode result;

    // Initialize the game state
    gs.Init();
    ngs.num_players = num_players;

    // Fill in a ggpo callbacks structure to pass to start_session.
    GGPOSessionCallbacks cb = CreateCallbacks();

#if defined(SYNC_TEST)
    result = GGPONet::ggpo_start_synctest(&ggpo, &cb, "vectorwar", num_players, sizeof(int), 1);
#else
    result = GGPONet::ggpo_start_session(&ggpo, &cb, "vectorwar", num_players, sizeof(int), localport);
#endif

    // automatically disconnect clients after 3000 ms and start our count-down timer
    // for disconnects after 1000 ms.   To completely disable disconnects, simply use
    // a value of 0 for ggpo_set_disconnect_timeout.
    GGPONet::ggpo_set_disconnect_timeout(ggpo, 3000);
    GGPONet::ggpo_set_disconnect_notify_start(ggpo, 1000);

    bool IsAnyPlayerRemote = false;
	UE_LOG(LogTemp, Warning, TEXT("About to add %d players"), num_players)
    int i;
    for (i = 0; i < num_players; i++) {
        GGPOPlayerHandle handle;
        result = GGPONet::ggpo_add_player(ggpo, players + i, &handle);
        UE_LOG(LogTemp, Warning, TEXT("Added player %d with result %d"), i, result)
        ngs.players[i].handle = handle;
        ngs.players[i].type = players[i].type;
        if (players[i].type == EGGPOPlayerType::LOCAL) {
            ngs.players[i].connect_progress = 100;
            ngs.local_player_handles[i] = handle;
            UE_LOG(LogTemp, Warning, TEXT("Added local player handle in index: %d"), i)
            ngs.SetConnectState(handle, EPlayerConnectState::Connecting);
            GGPONet::ggpo_set_frame_delay(ggpo, handle, FRAME_DELAY);
        }
        else {
            ngs.local_player_handles[i] = GGPO_INVALID_HANDLE;
            ngs.players[i].connect_progress = 0;
            IsAnyPlayerRemote = true;
            UE_LOG(LogTemp, Warning, TEXT("Added remote player handle in index: %d"), i)
        }
    }

    if (!IsAnyPlayerRemote) {
        GGPOErrorCode Result = GGPONet::ggpo_try_synchronize_local(ggpo);
        if (Result == GGPO_OK) {
            UE_LOG(LogTemp, Warning, TEXT("succeeded local synchronize"))
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("failed local synchronize: %d"), Result)
        }
    }
}

bool AGGPOGameOrchestrator::begin_game_callback(const char*)
{
    return true;
}

bool AGGPOGameOrchestrator::save_game_state_callback(unsigned char** buffer, int32* len, int32* checksum, int32)
{
    *len = sizeof(gs);
    *buffer = (unsigned char*)malloc(*len);
    if (!*buffer) {
        return false;
    }
    memcpy(*buffer, &gs, *len);
    *checksum = fletcher32_checksum((short*)*buffer, *len / 2);
    return true;
}
bool AGGPOGameOrchestrator::load_game_state_callback(unsigned char* buffer, int32 len)
{
    memcpy(&gs, buffer, len);
    return true;
}
bool AGGPOGameOrchestrator::log_game_state(char* filename, unsigned char* buffer, int32)
{
    return true;
}

void AGGPOGameOrchestrator::free_buffer(void* buffer)
{
    free(buffer);
}

bool AGGPOGameOrchestrator::advance_frame_callback(int32) {
    int inputs[2] = { 0 };
    int disconnect_flags;

    // Make sure we fetch new inputs from GGPO and use those to update
    // the game state instead of reading from the keyboard.
    GGPONet::ggpo_synchronize_input(ggpo, (void*)inputs, sizeof(int) * 2, &disconnect_flags);
    AdvanceFrame(inputs, disconnect_flags);
    return true;
}

bool AGGPOGameOrchestrator::on_event_callback(GGPOEvent* info) {
    int progress;
    switch (info->code) {
    case GGPO_EVENTCODE_CONNECTED_TO_PEER:
        ngs.SetConnectState(info->u.connected.player, EPlayerConnectState::Synchronizing);
        break;
    case GGPO_EVENTCODE_SYNCHRONIZING_WITH_PEER:
        progress = 100 * info->u.synchronizing.count / info->u.synchronizing.total;
        ngs.UpdateConnectProgress(info->u.synchronizing.player, progress);
        break;
    case GGPO_EVENTCODE_SYNCHRONIZED_WITH_PEER:
        ngs.UpdateConnectProgress(info->u.synchronized.player, 100);
        break;
    case GGPO_EVENTCODE_RUNNING:
        ngs.SetConnectState(EPlayerConnectState::Running);
        break;
    case GGPO_EVENTCODE_CONNECTION_INTERRUPTED:
        ngs.SetDisconnectTimeout(info->u.connection_interrupted.player,
            timeGetTime(),
            info->u.connection_interrupted.disconnect_timeout);
        break;
    case GGPO_EVENTCODE_CONNECTION_RESUMED:
        ngs.SetConnectState(info->u.connection_resumed.player, EPlayerConnectState::Running);
        break;
    case GGPO_EVENTCODE_DISCONNECTED_FROM_PEER:
        ngs.SetConnectState(info->u.disconnected.player, EPlayerConnectState::Disconnected);
        break;
    case GGPO_EVENTCODE_TIMESYNC:
        Sleep(1000 * info->u.timesync.frames_ahead / 60);
        break;
    }
    return true;
}

GGPOSessionCallbacks AGGPOGameOrchestrator::CreateCallbacks() {
    GGPOSessionCallbacks cb = { 0 };

    cb.begin_game = std::bind(&AGGPOGameOrchestrator::begin_game_callback, this, std::placeholders::_1);
    cb.save_game_state = std::bind(&AGGPOGameOrchestrator::save_game_state_callback, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    cb.load_game_state = std::bind(&AGGPOGameOrchestrator::load_game_state_callback, this,
        std::placeholders::_1, std::placeholders::_2);
    cb.log_game_state = std::bind(&AGGPOGameOrchestrator::log_game_state, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cb.free_buffer = std::bind(&AGGPOGameOrchestrator::free_buffer, this, std::placeholders::_1);
    cb.advance_frame = std::bind(&AGGPOGameOrchestrator::advance_frame_callback, this, std::placeholders::_1);
    cb.on_event = std::bind(&AGGPOGameOrchestrator::on_event_callback, this, std::placeholders::_1);

    return cb;
}

void AGGPOGameOrchestrator::AdvanceFrame(int32 inputs[], int32 disconnect_flags)
{
    gs.Update(inputs, disconnect_flags);

    // update the checksums to display in the top of the window.  this
    // helps to detect desyncs.
    ngs.now.framenumber = gs._framenumber;
    ngs.now.checksum = fletcher32_checksum((short*)&gs, sizeof(gs) / 2);
    if ((gs._framenumber % 90) == 0) {
        ngs.periodic = ngs.now;
    }

    // Notify ggpo that we've moved forward exactly 1 frame.
    GGPONet::ggpo_advance_frame(ggpo);

    // Update the performance monitor display.
    GGPOPlayerHandle handles[MAX_PLAYERS];
    int count = 0;
    for (int i = 0; i < ngs.num_players; i++) {
        if (ngs.players[i].type == EGGPOPlayerType::REMOTE) {
            handles[count++] = ngs.players[i].handle;
        }
    }
}

void AGGPOGameOrchestrator::Idle(int32 time)
{
    GGPONet::ggpo_idle(ggpo, time);
}

void AGGPOGameOrchestrator::TickGameState()
{
    int32 Input = GetLocalInputs();
    RunFrame(Input);

    // Network data
    TArray<FGGPONetworkStats> Network = GetNetworkStats();
    for (int32 i = 0; i < NetworkGraphData.Num(); i++)
    {
        TArray<FNetworkGraphData>* PlayerData = &NetworkGraphData[i].PlayerData;

        int32 Fairness;
        int32 LocalFairness = Network[i].timesync.local_frames_behind;
        int32 RemoteFairness = Network[i].timesync.remote_frames_behind;
        int32 Ping = Network[i].network.ping;

        if (LocalFairness < 0 && RemoteFairness < 0) {
            /*
             * Both think it's unfair (which, ironically, is fair).  Scale both and subtrace.
             */
            Fairness = abs(abs(LocalFairness) - abs(RemoteFairness));
        }
        else if (LocalFairness > 0 && RemoteFairness > 0) {
            /*
             * Impossible!  Unless the network has negative transmit time.  Odd....
             */
            Fairness = 0;
        }
        else {
            /*
             * They disagree.  Add.
             */
            Fairness = abs(LocalFairness) + abs(RemoteFairness);
        }

        FNetworkGraphData GraphData = FNetworkGraphData{ Fairness, RemoteFairness, Ping };
        PlayerData->Add(GraphData);

        while (PlayerData->Num() > NETWORK_GRAPH_STEPS)
        {
            PlayerData->RemoveAt(0);
        }
    }
}

void AGGPOGameOrchestrator::RunFrame(int32 local_input)
{
    GGPOErrorCode result = GGPO_OK;
    int disconnect_flags;
    int inputs[2] = { 0 };

    if (ngs.local_player_handles[0] != GGPO_INVALID_HANDLE) {
#if defined(SYNC_TEST)
        local_input = rand(); // test: use random inputs to demonstrate sync testing
#endif
        UE_LOG(LogTemp, Warning, TEXT("Local input: %d"), local_input)
        result = GGPONet::ggpo_add_local_input(ggpo, ngs.local_player_handles[0], &local_input, sizeof(local_input));

		if (!GGPO_SUCCEEDED(result)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to add first local input: %d"), result)
		}
    }

    if (ngs.local_player_handles[1] != GGPO_INVALID_HANDLE) {
#if defined(SYNC_TEST)
        local_input = rand(); // test: use random inputs to demonstrate sync testing
#endif
        UE_LOG(LogTemp, Warning, TEXT("Local input: %d"), local_input)
        result = GGPONet::ggpo_add_local_input(ggpo, ngs.local_player_handles[1], &local_input, sizeof(local_input));


		if (!GGPO_SUCCEEDED(result)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to add second local input: %d"), result)
		}
    }

    // synchronize these inputs with ggpo.  If we have enough input to proceed
    // ggpo will modify the input list with the correct inputs to use and
    // return 1.
    if (GGPO_SUCCEEDED(result)) {
        result = GGPONet::ggpo_synchronize_input(ggpo, (void*)inputs, sizeof(int) * 2, &disconnect_flags);
        if (GGPO_SUCCEEDED(result)) {
            // inputs[0] and inputs[1] contain the inputs for p1 and p2.  Advance
            // the game by 1 frame using those inputs.
            AdvanceFrame(inputs, disconnect_flags);
            UE_LOG(LogTemp, Warning, TEXT("synchronize_input success"))
        }
        else {
			UE_LOG(LogTemp, Warning, TEXT("Failed to synchronize inputs: %d"), result)
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Failed to add local inputs: %d"), result)
    }
}

int32 AGGPOGameOrchestrator::GetLocalInputs() {
    const UObject* world = (UObject*)GetWorld();
    ARBPlayerController* Controller = Cast<ARBPlayerController>(UGameplayStatics::GetPlayerController(world, 0));
    if (Controller)
    {
        return Controller->GetPlayerInput();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get input"))
		return 0;
    }
}

FTransform AGGPOGameOrchestrator::GetPlayerTransform(int32 PlayerIndex) {
    const Player player = gs._players[PlayerIndex];
    FVector Position = FVector(0, (float)player.position.x, (float)player.position.y);
    FQuat Rotation = FRotator(0, 0, 0).Quaternion();
    FTransform Result = FTransform(Rotation, Position);
    return Result;
}

// UE4: disallow windows platform types
//  this was enabled at the top of the file
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
