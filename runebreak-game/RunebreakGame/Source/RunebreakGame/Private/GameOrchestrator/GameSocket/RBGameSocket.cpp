#include "GameOrchestrator/GameSocket/RBGameSocket.h"
#include <RunebreakGame/Public/RBGameSession/Utilities/JsonUtils.h>
#include "Misc/Base64.h"

// todo: cache this
TSharedRef<FInternetAddr> FRBGameSocketConfig::GetRemoteAddr() {
	FIPv4Endpoint result;
	FString HostAndPortString = FString::Printf(TEXT("%s:%d"), *RemoteHost, RemotePort);
	FIPv4Endpoint::FromHostAndPort(HostAndPortString, result);
	return result.ToInternetAddr();
}

URBGameSocket::URBGameSocket()
{
	NetworkMonitor = CreateDefaultSubobject<UNetworkMonitor>(TEXT("NetworkMonitor"));
}

URBGameSocket::~URBGameSocket()
{
}

void URBGameSocket::Setup() {
	SocketSubsystem = nullptr;
	if (SocketSubsystem == nullptr)	SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	int32 MaxSendSize = 2 * 1024 * 1024;
	int32 BufferSize = 2 * 1024 * 1024;

	FIPv4Endpoint LocalEndpoint = FIPv4Endpoint(FIPv4Address::Any, SocketConfig.LocalPort);

	FIPv4Address RemoteAddress;
	FIPv4Address::Parse(SocketConfig.RemoteHost, RemoteAddress);

	FIPv4Endpoint RemoteEndpoint = FIPv4Endpoint(RemoteAddress, SocketConfig.RemotePort);

	SendSocket = nullptr;
	ReceiveSocket = nullptr;

	NetworkMonitor = NewObject<UNetworkMonitor>(this, TEXT("NetworkMonitor"));
	NetworkMonitor->PingImpl = [this](long long CurrentTime) {
		FPingMessage Message;
		Message.OriginTimestamp = CurrentTime;
		SendControlMessage(0, Message.ToJson());
	};

	if (SocketSubsystem != nullptr)
	{
		if (ReceiveSocket == nullptr)
		{
			 ReceiveSocket = FUdpSocketBuilder("RBGameSocket")
				.AsNonBlocking()
				.AsReusable()
				.BoundToEndpoint(LocalEndpoint)
				.WithSendBufferSize(MaxSendSize)
				.WithReceiveBufferSize(BufferSize)
				.WithBroadcast()
				.Build();
		}
		if (SendSocket == nullptr)
		{
			 SendSocket = FUdpSocketBuilder("RBGameSocket")
				.AsNonBlocking()
				.AsReusable()
				.WithSendBufferSize(MaxSendSize)
				.WithReceiveBufferSize(BufferSize)
				.WithBroadcast()
				.Build();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(PingTimerHandle, NetworkMonitor, &UNetworkMonitor::DoPing, PingIntervalSeconds, true);
}

void URBGameSocket::ReceivePendingMessages() {
	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	uint32 Size;
	while (ReceiveSocket->HasPendingData(Size))
	{
		uint8* Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		ReceiveSocket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *targetAddr);

		char ansiiData[1024];
		memcpy(ansiiData, ReceivedData.GetData(), BytesRead);
		ansiiData[BytesRead] = 0;

		FString data = ANSI_TO_TCHAR(ansiiData);
		FString log = FString::Printf(TEXT("got message: %s"), *data);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *log)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, log);
	}
}

bool URBGameSocket::SendControlMessage(int Type, FString Payload) {
	if (!SendSocket) {
		UE_LOG(LogTemp, Warning, TEXT("no socket was available"))
		return false;
	}

	FRBGameSocketMessage Message;
	Message.Type = Type;
	Message.Payload = Base64Encode(Payload);

	FString Json = ToJsonString(Message);

	int32 BytesSent = 0;

	TCHAR* serializedChar = Json.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);

	bool success = SendSocket->SendTo((uint8*)TCHAR_TO_UTF8(serializedChar), size, BytesSent, *SocketConfig.GetRemoteAddr());
	if (success) {
		UE_LOG(LogTemp, Warning, TEXT("Sent message: %s : was success: %s"), *Json, (success ? TEXT("true") : TEXT("false")))
		return true;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed sending message"))
		return false;
	}
}

void URBGameSocket::Teardown() {
	GetWorld()->GetTimerManager().ClearTimer(PingTimerHandle);

	if (SendSocket) {
		SocketSubsystem->DestroySocket(SendSocket);
	}
	if (ReceiveSocket) {
		SocketSubsystem->DestroySocket(ReceiveSocket);
	}

	SendSocket = nullptr;
	SocketSubsystem = nullptr;
}

FString URBGameSocket::Base64Encode(const FString& Source) {
	TArray<uint8> ByteArray;
	FTCHARToUTF8 StringSrc = FTCHARToUTF8(Source.GetCharArray().GetData());
	ByteArray.Append((uint8*)StringSrc.Get(), StringSrc.Length());
	return FBase64::Encode(ByteArray);
}

FString URBGameSocket::Base64Decode(const FString& Source) {
	FString Dest;
	TArray<uint8> ByteArray;
	bool Success = FBase64::Decode(Source, Dest);
	return Dest;
}
