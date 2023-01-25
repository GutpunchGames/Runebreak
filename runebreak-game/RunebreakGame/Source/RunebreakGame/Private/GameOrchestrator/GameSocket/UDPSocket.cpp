#include "GameOrchestrator/GameSocket/UDPSocket.h"

UUDPSocket::UUDPSocket()
{
}

UUDPSocket::~UUDPSocket()
{
}

void UUDPSocket::Setup(FUDPSocketConfig _SocketConfig) {
	SocketConfig = _SocketConfig;
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

	if (SocketSubsystem != nullptr)
	{
		if (ReceiveSocket == nullptr)
		{
			 ReceiveSocket = FUdpSocketBuilder("UDPReceiveSocket")
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
			 SendSocket = FUdpSocketBuilder("UDPSendSocket")
				.AsNonBlocking()
				.AsReusable()
				.WithSendBufferSize(MaxSendSize)
				.WithReceiveBufferSize(BufferSize)
				.WithBroadcast()
				.Build();
		}
	}
}

void UUDPSocket::SendMessage(FString& Bytes) {
	if (!SendSocket) {
		UE_LOG(LogTemp, Warning, TEXT("no socket was available"))
		return;
	}

	int32 BytesSent = 0;

	TCHAR* serializedChar = Bytes.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);

	bool success = SendSocket->SendTo((uint8*)TCHAR_TO_UTF8(serializedChar), size, BytesSent, *SocketConfig.GetRemoteAddr());
	if (success) {
		//UE_LOG(LogTemp, Warning, TEXT("Sent message: %s : was success: %s"), *Json, (success ? TEXT("true") : TEXT("false")))
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed sending message"))
		return;
	}
}

void UUDPSocket::ReceivePendingMessages() {
	if (!ReceiveSocket) {
		return;
	}

	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	uint32 Size;
	while (ReceiveSocket->HasPendingData(Size))
	{
		uint8* Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceiveDataBuffer.SetNumUninitialized(FMath::Min(Size, 65507u));
		ReceiveSocket->RecvFrom(ReceiveDataBuffer.GetData(), ReceiveDataBuffer.Num(), BytesRead, *targetAddr);

		char ansiiData[1024];
		memcpy(ansiiData, ReceiveDataBuffer.GetData(), BytesRead);
		ansiiData[BytesRead] = 0;

		FString Data = ANSI_TO_TCHAR(ansiiData);
		OnBytesReceivedDelegate.ExecuteIfBound(Data);
	}
}

void UUDPSocket::Teardown() {
	if (SendSocket) {
		SocketSubsystem->DestroySocket(SendSocket);
	}
	if (ReceiveSocket) {
		SocketSubsystem->DestroySocket(ReceiveSocket);
	}

	SendSocket = nullptr;
	SocketSubsystem = nullptr;
}

// todo: cache this
TSharedRef<FInternetAddr> FUDPSocketConfig::GetRemoteAddr() {
	FIPv4Endpoint result;
	FString HostAndPortString = FString::Printf(TEXT("%s:%d"), *RemoteHost, RemotePort);
	FIPv4Endpoint::FromHostAndPort(HostAndPortString, result);
	return result.ToInternetAddr();
}
