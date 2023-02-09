// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOrchestrator/GameLogger/GameLogger.h"

UGameLogger::UGameLogger()
{ 
}

UGameLogger::~UGameLogger()
{
}

void UGameLogger::Initialize(FString _FilePath) {
	FilePath = _FilePath;
	UE_LOG(LogTemp, Warning, TEXT("Game Log: initialized file path: %s"), *FilePath);
}

void UGameLogger::LogGameStart(const FString& PlayerCharacter1, const FString& PlayerCharacter2, const FString& Stage) {
	const FString GameStartLog = FString::Format(*GameStartFormat, { PlayerCharacter1, PlayerCharacter2, Stage });
	AppendBytes(GameStartLog);
	UE_LOG(LogTemp, Warning, TEXT("Game Log: game start file path: %s"), *FilePath);
}

void UGameLogger::LogGameEnd() {
	AppendBytes(GameEndFormat);
}

void UGameLogger::LogTickStart(int Frame, FString Checksum) {
	const FString Log = FString::Format(*TickStartFormat, { Frame, Checksum });
	AppendBytes(Log);
}

void UGameLogger::LogTickEnd(int Frame, FString Checksum) {
	const FString Log = FString::Format(*TickEndFormat, { Frame, Checksum});
	AppendBytes(Log);
}

void UGameLogger::LogRollback(int Frame, FString Checksum) {
	const FString Log = FString::Format(*RollToFormat, { Frame, Checksum});
	AppendBytes(Log);
}

static const FString SimulateFrameFormat = TEXT("SIM\t{0}\n\tCHK_START {1}\n\tCHK_END {2}\n\tI1\t{3}\n\tI2\t{4}");
void UGameLogger::LogSimulate(int Frame, FString StartChecksum, FString EndChecksum, FString Input1, FString Input2) {
	const FString Log = FString::Format(*SimulateFrameFormat, { Frame, StartChecksum, EndChecksum, Input1, Input2 });
	AppendBytes(Log);
}

void UGameLogger::LogSyncReceive(int Player, const FSyncMessage& SyncMessage) {
	const FString HeaderLog = FString::Format(*SyncReceiveHeaderFormat, { Player, SyncMessage.OriginFrame, SyncMessage.RecentInputs.Num(), SyncMessage.FrameAck });
	AppendBytes(HeaderLog);

	for (int i = 0; i < SyncMessage.RecentInputs.Num(); i++) {
		FInput Input = SyncMessage.RecentInputs[i];
		// todo: no naive input tostring
		FString InputLog = FString::Format(TEXT("\t\t{0} {1}"), { Input.Frame, Input.ToString() });
		AppendBytes(InputLog);
	}
}

void UGameLogger::LogSyncSend(int Player, const FSyncMessage& SyncMessage) {
	const FString HeaderLog = FString::Format(*SyncSendHeaderFormat, { Player, SyncMessage.OriginFrame, SyncMessage.RecentInputs.Num(), SyncMessage.FrameAck });
	AppendBytes(HeaderLog);

	for (int i = 0; i < SyncMessage.RecentInputs.Num(); i++) {
		FInput Input = SyncMessage.RecentInputs[i];
		// todo: no naive input tostring
		FString InputLog = FString::Format(TEXT("\t\t{0} {1}"), { Input.Frame, Input.ToString() });
		AppendBytes(InputLog);
	}
}

void UGameLogger::AppendBytes(const FString& Bytes) {
	FString TestFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/" + FilePath);
	UE_LOG(LogTemp, Warning, TEXT("GameLog: my file path: %s"), *TestFilePath);
	FFileHelper::SaveStringToFile(Bytes + "\n", *TestFilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}
