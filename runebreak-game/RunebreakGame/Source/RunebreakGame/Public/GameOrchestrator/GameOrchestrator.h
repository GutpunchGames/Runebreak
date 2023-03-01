// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "include/ggponet.h"
#include "GameFramework/Actor.h"
#include "GameOrchestrator/RBGameState.h"
#include "GameOrchestrator/RBNonGameState.h"
#include "GameOrchestrator.generated.h"

#define NETWORK_GRAPH_STEPS 720
#define SYNC_TEST

UENUM(BlueprintType)
enum class ENetworkGraphType : uint8
{
	PING           UMETA(DisplayName = "Ping"),
	SYNC           UMETA(DisplayName = "Fairness"),
	REMOTE_SYNC    UMETA(DisplayName = "Remote Fairness"),
};

USTRUCT(BlueprintType)
struct FNetworkGraphData {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32   Fairness;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32   RemoteFairness;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32   Ping;
};

USTRUCT(BlueprintType)
struct FNetworkGraphPlayer {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FNetworkGraphData> PlayerData;
};

UCLASS()
class RUNEBREAKGAME_API AGameOrchestrator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameOrchestrator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Called from BeginPlay() after creating the game state.
	 * Can be overridden by a blueprint to create actors that represent the game state.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GGPO")
	void OnSessionStarted();
	virtual void OnSessionStarted_Implementation();

	TArray<FNetworkGraphPlayer> NetworkGraphData;

	GameState gs = { 0 };
	NonGameState ngs = { 0 };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTransform GetPlayerTransform(int32 PlayerIndex);

private:
	/*
	 * VectorWar_Init --
	 *
	 * Initialize the vector war game.  This initializes the game state and
	 * creates a new network session.
	 */
	void Init(uint16 localport, int32 num_players, GGPOPlayer* players, int32 num_spectators);

	/** Starts a GGPO game session. */
	bool TryStartGGPOPlayerSession(int32 NumPlayers, const UGGPONetwork* NetworkAddresses);

	/** Gets the inputs from the local player. */
	int32 GetLocalInputs();

	/*
	 * VectorWar_RunFrame --
	 *
	 * Run a single frame of the game.
	 */
	void RunFrame(int32 local_input);
	/*
	 * VectorWar_AdvanceFrame --
	 *
	 * Advances the game state by exactly 1 frame using the inputs specified
	 * for player 1 and player 2.
	 */
	void AdvanceFrame(int32 inputs[], int32 disconnect_flags);
	/*
	 * VectorWar_Idle --
	 *
	 * Spend our idle time in ggpo so it can use whatever time we have left over
	 * for its internal bookkeeping.
	 */
	void Idle(int32 time);
	void Exit();

	/** Gets stats about the network connection. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game State")
	TArray<FGGPONetworkStats> GetNetworkStats();

	bool bSessionStarted;

	float ElapsedTime;

	GGPOSession* ggpo = nullptr;

private:
	void TickGameState();
	/** Gets a GGPOSessionCallbacks object with its callback functions assigned. */
	GGPOSessionCallbacks CreateCallbacks();

	/*
	 * The begin game callback.  We don't need to do anything special here,
	 * so just return true.
	 */
	bool __cdecl begin_game_callback(const char*);
	/*
	 * Save the current state to a buffer and return it to GGPO via the
	 * buffer and len parameters.
	 */
	bool __cdecl save_game_state_callback(unsigned char** buffer, int32* len, int32* checksum, int32);
	/*
	 * Makes our current state match the state passed in by GGPO.
	 */
	bool __cdecl load_game_state_callback(unsigned char* buffer, int32 len);
	/*
	 * Log the gamestate.  Used by the synctest debugging tool.
	 */
	bool __cdecl log_game_state(char* filename, unsigned char* buffer, int32);
	/*
	 * Free a save state buffer previously returned in vw_save_game_state_callback.
	 */
	void __cdecl free_buffer(void* buffer);
	/*
	 * Notification from GGPO we should step foward exactly 1 frame
	 * during a rollback.
	 */
	bool __cdecl advance_frame_callback(int32);
	/*
	 * Notification from GGPO that something has happened.  Update the status
	 * text at the bottom of the screen to notify the user.
	 */
	bool __cdecl on_event_callback(GGPOEvent* info);
};
