// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Networking.h"
#include "CoreMinimal.h"
#include "UDPSocket.generated.h"

DECLARE_DELEGATE_OneParam(FOnBytesReceived, const FString&);

USTRUCT(BlueprintType)
struct FUDPSocketConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString RemoteHost;
	UPROPERTY(BlueprintReadWrite)
	int RemotePort;
	UPROPERTY(BlueprintReadWrite)
	int LocalPort;

	TSharedRef<FInternetAddr> GetRemoteAddr();
};

UCLASS()
class RUNEBREAKGAME_API UUDPSocket : public UObject
{
	GENERATED_BODY()

public:
	UUDPSocket();
	~UUDPSocket();

	void Setup(FUDPSocketConfig _SocketConfig);
	void Teardown();

	void SendMessage(FString& Bytes);
	void ReceivePendingMessages();

	TArray<uint8> ReceiveDataBuffer;

	FOnBytesReceived OnBytesReceivedDelegate;

private:
	UPROPERTY()
	FUDPSocketConfig SocketConfig;
	ISocketSubsystem* SocketSubsystem;

	FSocket* SendSocket;
	FSocket* ReceiveSocket;
};
