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

	Socket = nullptr;

	if (SocketSubsystem != nullptr)
	{
		if (Socket == nullptr)
		{
			Socket = FUdpSocketBuilder("RBGameSocket")
				.AsNonBlocking()
				.AsReusable()
				.BoundToEndpoint(LocalEndpoint)
				.WithSendBufferSize(MaxSendSize)
				.WithReceiveBufferSize(BufferSize)
				.WithBroadcast();
		}
	}
}

void URBGameSocket::ReceiveMessage() {
	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	uint32 Size;
	while (Socket->HasPendingData(Size))
	{
		UE_LOG(LogTemp, Warning, TEXT("Had data"))
		uint8* Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		Socket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *targetAddr);

		char ansiiData[1024];
		memcpy(ansiiData, ReceivedData.GetData(), BytesRead);
		ansiiData[BytesRead] = 0;

		FString data = ANSI_TO_TCHAR(ansiiData);
		UE_LOG(LogTemp, Warning, TEXT("Received data: %s"), *data)
	}
}

bool URBGameSocket::SendMessage(FString Message) {
	if (!Socket) {
		UE_LOG(LogTemp, Warning, TEXT("no socket was available"))
		return false;
	}

	int32 BytesSent = 0;
	FTimespan waitTime = FTimespan(10);

	TCHAR* serializedChar = Message.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);

	bool success = Socket->SendTo((uint8*)TCHAR_TO_UTF8(serializedChar), size, BytesSent, *SocketConfig.GetRemoteAddr());
	UE_LOG(LogTemp, Warning, TEXT("Sent message: %s : %s : Address - %s : BytesSent - %d"), *Message, (success ? TEXT("true") : TEXT("false")), &BytesSent);

	if (success && BytesSent > 0) return true;
	else return false;
}

void URBGameSocket::Teardown() {
	if (Socket) {
		SocketSubsystem->DestroySocket(Socket);
		Socket = nullptr;
		SocketSubsystem = nullptr;
	}
}
