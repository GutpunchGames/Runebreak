// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"GameOrchestrator/GameSocket/NetworkMonitor.h"
#include"GameOrchestrator/GameSocket/InputsMessage.h"
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/UDPSocket.h>
#include "RBGameSocket.generated.h"

DECLARE_DELEGATE_OneParam(FOnInputsReceived, const FInputsMessage&);

USTRUCT(BlueprintType)
struct FRBGameSocketConfig {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUDPSocketConfig UDPSocketConfig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHost;
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

	void SendControlMessage(int Type, FString Payload);
	void ReceivePendingMessages();

	UFUNCTION()
	void HandleMessage(const FString& Bytes);

	UPROPERTY(BlueprintReadOnly)
	UNetworkMonitor* NetworkMonitor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PingIntervalSeconds;

	UPROPERTY(BlueprintReadOnly)
	ERBGameSocketState SocketState;

	UUDPSocket* Socket;

	FOnInputsReceived OnInputsReceivedDelegate;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void HandleControlMessage(FRBGameSocketMessage Message);
	/* Handle to manage the timer */
	FTimerHandle PingTimerHandle;
};
