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

}

void UGameLogger::LogSimulate(int Frame, FString Input1, FString Input2) {
	const FString Log = FString::Format(*SimulateFrameFormat, { Frame, Input1, Input2 });
	AppendBytes(Log);
}

void UGameLogger::LogSyncReceive(const FSyncMessage& SyncMessage) {

}

void UGameLogger::LogSyncSend(const FSyncMessage& SyncMessage) {

}

void UGameLogger::AppendBytes(const FString& Bytes) {
	FString TestFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/GameLog.txt");
	UE_LOG(LogTemp, Warning, TEXT("GameLog: my file path: %s"), *TestFilePath);
	FFileHelper::SaveStringToFile(Bytes + "\n", *TestFilePath, FFileHelper::EEncodingOptions::ForceUTF8, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}
