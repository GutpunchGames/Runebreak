#include "GameOrchestrator/GameOrchestrator.h"
#include "GameOrchestrator/RBPlayerController.h"
#include "GGPOGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#define FRAME_DELAY 2
#define FRAME_RATE 60
#define ONE_FRAME (1.0f / FRAME_RATE)

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

    ElapsedTime += DeltaTime;

    int32 IdleMs = (int32)(ONE_FRAME - (int32)(ElapsedTime * 1000));
    Idle(FMath::Max(0, IdleMs - 1));
    while (ElapsedTime >= ONE_FRAME) {
        TickGameState();
        ElapsedTime -= ONE_FRAME;
    }
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
    int32 Offset = 0;
    GGPOPlayer Players[GGPO_MAX_SPECTATORS + GGPO_MAX_PLAYERS];
    int32 NumSpectators = 0;

    uint16 LocalPort;

    // If there are no remote players...
    if (NetworkAddresses == nullptr)
    {
        Players[0].size = sizeof(Players[0]);
        Players[0].player_num = 1;
        Players[0].type = EGGPOPlayerType::LOCAL;

        LocalPort = 7000;
        NumPlayers = 1;
    }
    else
    {
        if (NumPlayers > NetworkAddresses->NumPlayers())
            return false;

        LocalPort = NetworkAddresses->GetLocalPort();

        int32 i;
        for (i = 0; i < NumPlayers; i++)
        {
            Offset++;

            Players[i].size = sizeof(Players[i]);
            Players[i].player_num = i + 1;
            // The local player
            if (i == NetworkAddresses->GetPlayerIndex()) {
                Players[i].type = EGGPOPlayerType::LOCAL;
                continue;
            }

            Players[i].type = EGGPOPlayerType::REMOTE;
            Players[i].u.remote.port = (uint16)NetworkAddresses->GetAddress(i)->GetPort();
            NetworkAddresses->GetAddress(i)->GetIpAddress(Players[i].u.remote.ip_address);
        }
        // these are spectators...
        while (Offset < NetworkAddresses->NumPlayers()) {
            Offset++;

            Players[i].type = EGGPOPlayerType::SPECTATOR;
            Players[i].u.remote.port = (uint16)NetworkAddresses->GetAddress(i)->GetPort();
            NetworkAddresses->GetAddress(i)->GetIpAddress(Players[i].u.remote.ip_address);

            i++;
            NumSpectators++;
        }
    }

    Init(LocalPort, NumPlayers, Players, NumSpectators);

    UE_LOG(LogTemp, Display, TEXT("GGPO session started"));

    return true;
}

void AGameOrchestrator::OnSessionStarted_Implementation() { }

void AGameOrchestrator::Init(uint16 localport, int32 num_players, GGPOPlayer* players, int32 num_spectators)
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

    int i;
    for (i = 0; i < num_players + num_spectators; i++) {
        GGPOPlayerHandle handle;
        result = GGPONet::ggpo_add_player(ggpo, players + i, &handle);
        ngs.players[i].handle = handle;
        ngs.players[i].type = players[i].type;
        if (players[i].type == EGGPOPlayerType::LOCAL) {
            ngs.players[i].connect_progress = 100;
            ngs.local_player_handle = handle;
            ngs.SetConnectState(handle, EPlayerConnectState::Connecting);
            GGPONet::ggpo_set_frame_delay(ggpo, handle, FRAME_DELAY);
        }
        else {
            ngs.players[i].connect_progress = 0;
        }
    }

    GGPONet::ggpo_try_synchronize_local(ggpo);
}

bool AGameOrchestrator::begin_game_callback(const char*)
{
    return true;
}
bool AGameOrchestrator::save_game_state_callback(unsigned char** buffer, int32* len, int32* checksum, int32)
{
    //*len = sizeof(gs);
    //*buffer = (unsigned char*)malloc(*len);
    //if (!*buffer) {
    //    return false;
    //}
    //memcpy(*buffer, &gs, *len);
    //*checksum = fletcher32_checksum((short*)*buffer, *len / 2);
    return true;
}
bool AGameOrchestrator::load_game_state_callback(unsigned char* buffer, int32 len)
{
    //memcpy(&gs, buffer, len);
    return true;
}
bool AGameOrchestrator::log_game_state(char* filename, unsigned char* buffer, int32)
{
    //FILE* fp = nullptr;
    //fopen_s(&fp, filename, "w");
    //if (fp) {
    //    GameState* gamestate = (GameState*)buffer;
    //    fprintf(fp, "GameState object.\n");
    //    fprintf(fp, "  bounds: %ld,%ld x %ld,%ld.\n", gamestate->_bounds.left, gamestate->_bounds.top,
    //        gamestate->_bounds.right, gamestate->_bounds.bottom);
    //    fprintf(fp, "  num_ships: %d.\n", gamestate->_num_ships);
    //    for (int i = 0; i < gamestate->_num_ships; i++) {
    //        Ship* ship = gamestate->_ships + i;
    //        fprintf(fp, "  ship %d position:  %.4f, %.4f\n", i, ship->position.x, ship->position.y);
    //        fprintf(fp, "  ship %d velocity:  %.4f, %.4f\n", i, ship->velocity.dx, ship->velocity.dy);
    //        fprintf(fp, "  ship %d radius:    %d.\n", i, ship->radius);
    //        fprintf(fp, "  ship %d heading:   %d.\n", i, ship->heading);
    //        fprintf(fp, "  ship %d health:    %d.\n", i, ship->health);
    //        fprintf(fp, "  ship %d speed:     %d.\n", i, ship->speed);
    //        fprintf(fp, "  ship %d cooldown:  %d.\n", i, ship->cooldown);
    //        fprintf(fp, "  ship %d score:     %d.\n", i, ship->score);
    //        for (int j = 0; j < MAX_BULLETS; j++) {
    //            Bullet* bullet = ship->bullets + j;
    //            fprintf(fp, "  ship %d bullet %d: %.2f %.2f -> %.2f %.2f.\n", i, j,
    //                bullet->position.x, bullet->position.y,
    //                bullet->velocity.dx, bullet->velocity.dy);
    //        }
    //    }
    //    fclose(fp);
    //}
    return true;
}
void AGameOrchestrator::free_buffer(void* buffer)
{
    free(buffer);
}
bool AGameOrchestrator::advance_frame_callback(int32)
{
    int inputs[2] = { 0 };
    int disconnect_flags;

    // Make sure we fetch new inputs from GGPO and use those to update
    // the game state instead of reading from the keyboard.
    GGPONet::ggpo_synchronize_input(ggpo, (void*)inputs, sizeof(int) * 2, &disconnect_flags);
    AdvanceFrame(inputs, disconnect_flags);
    return true;
}
bool AGameOrchestrator::on_event_callback(GGPOEvent* info)
{
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
        // todo: support this
        //ngs.SetDisconnectTimeout(info->u.connection_interrupted.player,
        //    get_time(),
        //    info->u.connection_interrupted.disconnect_timeout);
        break;
    case GGPO_EVENTCODE_CONNECTION_RESUMED:
        ngs.SetConnectState(info->u.connection_resumed.player, EPlayerConnectState::Running);
        break;
    case GGPO_EVENTCODE_DISCONNECTED_FROM_PEER:
        ngs.SetConnectState(info->u.disconnected.player, EPlayerConnectState::Disconnected);
        break;
    case GGPO_EVENTCODE_TIMESYNC:
        // todo: support this
        //Sleep(1000 * info->u.timesync.frames_ahead / 60);
        break;
    }
    return true;
}

GGPOSessionCallbacks AGameOrchestrator::CreateCallbacks()
{
    GGPOSessionCallbacks cb = { 0 };

    cb.begin_game = std::bind(&AGameOrchestrator::begin_game_callback, this, std::placeholders::_1);
    cb.save_game_state = std::bind(&AGameOrchestrator::save_game_state_callback, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    cb.load_game_state = std::bind(&AGameOrchestrator::load_game_state_callback, this,
        std::placeholders::_1, std::placeholders::_2);
    cb.log_game_state = std::bind(&AGameOrchestrator::log_game_state, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    cb.free_buffer = std::bind(&AGameOrchestrator::free_buffer, this, std::placeholders::_1);
    cb.advance_frame = std::bind(&AGameOrchestrator::advance_frame_callback, this, std::placeholders::_1);
    cb.on_event = std::bind(&AGameOrchestrator::on_event_callback, this, std::placeholders::_1);

    return cb;
}

void AGameOrchestrator::AdvanceFrame(int32 inputs[], int32 disconnect_flags)
{
    gs.Update(inputs, disconnect_flags);

    // update the checksums to display in the top of the window.  this
    // helps to detect desyncs.
    ngs.now.framenumber = gs._framenumber;
    //ngs.now.checksum = fletcher32_checksum((short*)&gs, sizeof(gs) / 2);
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

void AGameOrchestrator::Idle(int32 time)
{
    GGPONet::ggpo_idle(ggpo, time);
}

void AGameOrchestrator::TickGameState()
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

void AGameOrchestrator::RunFrame(int32 local_input)
{
    GGPOErrorCode result = GGPO_OK;
    int disconnect_flags;
    int inputs[2] = { 0 };

    if (ngs.local_player_handle != GGPO_INVALID_HANDLE) {
#if defined(SYNC_TEST)
        local_input = rand(); // test: use random inputs to demonstrate sync testing
#endif
        result = GGPONet::ggpo_add_local_input(ggpo, ngs.local_player_handle, &local_input, sizeof(local_input));
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
        }
    }
}

int32 AGameOrchestrator::GetLocalInputs()
{
    const UObject* world = (UObject*)GetWorld();
    ARBPlayerController* Controller = Cast<ARBPlayerController>(UGameplayStatics::GetPlayerController(world, 0));
    if (Controller)
    {
        UE_LOG(LogTemp, Warning, TEXT("Got input"))
        return Controller->GetPlayerInput();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get input"))
		return 0;
    }
}

FTransform AGameOrchestrator::GetPlayerTransform(int32 PlayerIndex) {
    const Player player = gs._players[PlayerIndex];
    FVector Position = FVector(0, (float)player.position.x, (float)player.position.y);
    FQuat Rotation = FRotator(0, 0, 0).Quaternion();
    FTransform Result = FTransform(Rotation, Position);
    return Result;
}
