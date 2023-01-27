// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"GameOrchestrator/GameSocket/GameSocketMessages.h"
#include"GameOrchestrator/GameSocket/NetworkMonitor.h"
#include"GameOrchestrator/GameSocket/InputsMessage.h"
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/UDPSocket.h>
#include "RBGameSocket.generated.h"

DECLARE_DELEGATE_OneParam(FOnInputsReceived, const FInputsMessage&);

static const int MESSAGE_TYPE_PING = 0;
static const int MESSAGE_TYPE_PONG = 1;
static const int MESSAGE_TYPE_INPUTS = 2;

USTRUCT(BlueprintType)
struct FRBGameSocketConfig {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUDPSocketConfig UDPSocketConfig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LogToScreen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PingIntervalSecs = 1;
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

UCLASS(Blueprintable)
class RUNEBREAKGAME_API ARBGameSocket : public AActor
{
	GENERATED_BODY()

public:
	ARBGameSocket();
	~ARBGameSocket();

	UFUNCTION(BlueprintCallable)
	void Setup();

	UFUNCTION(BlueprintCallable)
	void Teardown();

	UPROPERTY(BlueprintReadWrite)
	FRBGameSocketConfig SocketConfig;

	void SendPing(int LocalFrame);

	void SendControlMessage(int Type, FString Payload);
	void ReceivePendingMessages();

	UFUNCTION()
	void HandleMessage(const FString& Bytes);

	UPROPERTY(BlueprintReadOnly)
	UNetworkMonitor* NetworkMonitor;

	UPROPERTY(BlueprintReadOnly)
	ERBGameSocketState SocketState;

	UPROPERTY()
	UUDPSocket* Socket;

	UPROPERTY()
	int CurrentFrame;

	FOnInputsReceived OnInputsReceivedDelegate;

	virtual void Tick(float DeltaTime) override;

private:
	bool IsSetup;
};
