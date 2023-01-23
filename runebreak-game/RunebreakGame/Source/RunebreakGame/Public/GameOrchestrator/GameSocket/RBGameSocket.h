// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include"GameOrchestrator/GameSocket/NetworkMonitor.h"
#include "RBGameSocket.generated.h"

USTRUCT(BlueprintType)
struct FRBGameSocketConfig {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RemoteHost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RemotePort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LocalPort;

	TSharedRef<FInternetAddr> GetRemoteAddr();
};

UENUM(BlueprintType)
enum class ERBGameSocketState : uint8 {
	Uninitialized = 0x0,
	Syncing = 0x1,
	Playing = 0x2
};

USTRUCT(BlueprintType)
struct FRBGameSocketMessage {
	GENERATED_BODY()

public:
	UPROPERTY()
	int Type;

	UPROPERTY()
	FString Payload; // base 64 encoded JSON for control messages.
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RUNEBREAKGAME_API URBGameSocket : public UActorComponent
{
	GENERATED_BODY()

public:
	URBGameSocket();
	~URBGameSocket();

	UFUNCTION(BlueprintCallable)
	void Setup();

	UFUNCTION(BlueprintCallable)
	void Teardown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRBGameSocketConfig SocketConfig;

	bool SendControlMessage(int Type, FString Payload);

	void ReceivePendingMessages();

	UPROPERTY(BlueprintReadOnly)
	UNetworkMonitor* NetworkMonitor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PingIntervalSeconds;

	ISocketSubsystem* SocketSubsystem;
	FSocket* SendSocket;
	FSocket* ReceiveSocket;
	TArray<uint8> ReceivedData;

private:
	/* Handle to manage the timer */
	FTimerHandle PingTimerHandle;

	FString Base64Encode(const FString& Source);
	FString Base64Decode(const FString& Source);
};
