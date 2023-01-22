#include "GameOrchestrator/GameSocket/RBGameSocket.h"

// todo: cache this
TSharedRef<FInternetAddr> FRBGameSocketConfig::GetRemoteAddr() {
	FIPv4Endpoint result;
	FString HostAndPortString = FString::Printf(TEXT("%s:%d"), *RemoteHost, RemotePort);
	FIPv4Endpoint::FromHostAndPort(HostAndPortString, result);
	return result.ToInternetAddr();
}

URBGameSocket::URBGameSocket()
{

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

	FIPv4Address Addr = FIPv4Address::Any;

	if (SocketSubsystem != nullptr)
	{
		if (ReceiveSocket == nullptr)
		{
			 ReceiveSocket = FUdpSocketBuilder("RBGameSocket")
				.AsNonBlocking()
				.AsReusable()
				.BoundToAddress(Addr)
				.BoundToPort(9010)
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
				.BoundToAddress(Addr)
				.BoundToPort(9012)
				.WithSendBufferSize(MaxSendSize)
				.WithReceiveBufferSize(BufferSize)
				.WithBroadcast()
				.Build();
		}
	}
}

void URBGameSocket::ReceiveMessage() {
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
		UE_LOG(LogTemp, Warning, TEXT("Received data: %s"), *data)
	}
	UE_LOG(LogTemp, Warning, TEXT("Receive message END"))
}

bool URBGameSocket::SendMessage(FString Message) {
	if (!SendSocket) {
		UE_LOG(LogTemp, Warning, TEXT("no socket was available"))
		return false;
	}

	int32 BytesSent = 0;

	TCHAR* serializedChar = Message.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);

	bool success = SendSocket->SendTo((uint8*)TCHAR_TO_UTF8(serializedChar), size, BytesSent, *SocketConfig.GetRemoteAddr());
	if (success) {
		UE_LOG(LogTemp, Warning, TEXT("Sent message: %s : %s"), *Message, (success ? TEXT("true") : TEXT("false")))
		return true;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed sending message"))
		return false;
	}
}

void URBGameSocket::Teardown() {
	if (SendSocket) {
		SocketSubsystem->DestroySocket(SendSocket);
	}
	if (ReceiveSocket) {
		SocketSubsystem->DestroySocket(ReceiveSocket);
	}

	SendSocket = nullptr;
	SocketSubsystem = nullptr;
}
