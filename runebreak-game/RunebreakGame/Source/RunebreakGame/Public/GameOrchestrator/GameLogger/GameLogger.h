// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Misc/FileHelper.h"
#include "GameOrchestrator/GameSocket/GameSocketMessages.h"
#include "GameLogger.generated.h"

static const FString GameStartFormat = TEXT("GAME\n\tP1 {0}\n\tP2 {1}\n\tSTG {2}");
static const FString GameEndFormat = TEXT("ENDGAME");
static const FString TickStartFormat = TEXT("TICK {0} {1}");
static const FString TickEndFormat = TEXT("ENDTICK {0} {1}");
static const FString SimulateFrameFormat = TEXT("SIM {0}\n\tI1 {1}\n\tI2 {2}");

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
	void LogSyncReceive(const FSyncMessage& SyncMessage);
	UFUNCTION()
	void LogSyncSend(const FSyncMessage& SyncMessage);

private:
	UPROPERTY()
	FString FilePath;

	UFUNCTION()
	void AppendBytes(const FString& Bytes);
};
