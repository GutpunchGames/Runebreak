// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
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

	UFUNCTION(BlueprintCallable)
	bool SendMessage(FString Message);

	UFUNCTION(BlueprintCallable)
	void ReceiveMessage();

	ISocketSubsystem* SocketSubsystem;
	FSocket* Socket;
	TArray<uint8> ReceivedData;
};
