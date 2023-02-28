// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "include/ggponet.h"
#include "GameFramework/Actor.h"
#include "GameOrchestrator.generated.h"

#define NETWORK_GRAPH_STEPS 720

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

private:
	/** Starts a GGPO game session. */
	bool TryStartGGPOPlayerSession(int32 NumPlayers, const UGGPONetwork* NetworkAddresses);

	/** Gets stats about the network connection. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game State")
	TArray<FGGPONetworkStats> GetNetworkStats();

	bool bSessionStarted;

	float ElapsedTime;

};
