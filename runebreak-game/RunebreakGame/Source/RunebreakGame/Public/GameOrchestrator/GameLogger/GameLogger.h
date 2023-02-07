// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Misc/FileHelper.h"
#include "GameOrchestrator/GameSocket/GameSocketMessages.h"
#include "GameLogger.generated.h"

static const FString GameStartFormat = TEXT("GAME\n\tP1\t{0}\n\tP2\t{1}\n\tSTG\t{2}");
static const FString GameEndFormat = TEXT("ENDGAME");
static const FString TickStartFormat = TEXT("STARTF\t{0}\t{1}");
static const FString TickEndFormat = TEXT("ENDF\t{0}\t{1}");
static const FString SimulateFrameFormat = TEXT("SIM\t{0}\n\tI1\t{1}\n\tI2\t{2}");
static const FString RollToFormat = TEXT("ROLLTO\t{0}\t{1}");
static const FString SyncReceiveHeaderFormat = TEXT("SYNC_RECV\t{0}\t{1}\t{2}\n\tACK\t{3}");
static const FString SyncSendHeaderFormat = TEXT("SYNC_SEND\t{0}\t{1}\t{2}\n\tACK\t{3}");

/**
 * 
 Write logs like this....
 eventually should include what we broadcast
 TODO: 
 - change ISEND/IRECV inputs to input deltas when the socket API changes

GAME
	P1 <char>
	P2 <char>
	STG <stage>
TICK <frame> <chksum>
	# if we receive remote input...
	SYNC_RECV <player> <start_frame> <count>
		ACK <frame_ack>
		<frame> <input>
		<frame> <input>
		...
	# if we broadcast input...
	SYNC_SEND <player> <start_frame> <count>
		ACK <frame_ack>
		<frame> <input>
		<frame> <input>
		...
	# if a rollback happens...
	ROLLTO <frame>
		RESTORE <chksum>
	# simulate a frame...
	SIM <frame>
		I1 <input>
		I2 <input>
		CHK <chksum>
ENDTICK <frame> <chksum>
ENDGAME
 */
UCLASS()
class RUNEBREAKGAME_API UGameLogger : public UObject
{
	GENERATED_BODY()

public:
	UGameLogger();
	~UGameLogger();

	UFUNCTION()
	void Initialize(FString FilePath);

	UFUNCTION()
	void LogGameStart(const FString& PlayerCharacter1, const FString& PlayerCharacter2, const FString& Stage);
	UFUNCTION()
	void LogGameEnd();
	UFUNCTION()
	void LogTickStart(int Frame, FString Checksum);
	UFUNCTION()
	void LogTickEnd(int Frame, FString Checksum);
	UFUNCTION()
	void LogRollback(int Frame, FString Checksum);
	UFUNCTION()
	void LogSimulate(int Frame, FString Input1, FString Input2);
	UFUNCTION()
	void LogSyncReceive(int Player, const FSyncMessage& SyncMessage);
	UFUNCTION()
	void LogSyncSend(int Player, const FSyncMessage& SyncMessage);

private:
	UPROPERTY()
	FString FilePath;

	UFUNCTION()
	void AppendBytes(const FString& Bytes);
};
