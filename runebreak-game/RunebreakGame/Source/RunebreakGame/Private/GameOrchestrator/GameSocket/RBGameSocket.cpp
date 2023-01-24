#include "GameOrchestrator/GameSocket/RBGameSocket.h"
#include <RunebreakGame/Public/RBGameSession/Utilities/JsonUtils.h>
#include "Kismet/KismetStringLibrary.h"
#include <Utilities/TimeUtilities.h>
#include <Utilities/Base64Utilities.h>

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
	SocketState = ERBGameSocketState::Uninitialized;

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
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
	NetworkMonitor->PingImpl = [this](FPingMessage PingMessage) {
		SendControlMessage(0, PingMessage.ToJson());
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
	if (!ReceiveSocket) {
		return;
	}

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
		FRBGameSocketMessage Message;
		FromJson<FRBGameSocketMessage>(data, &Message);
		HandleControlMessage(Message);
	}
}

bool URBGameSocket::SendControlMessage(int Type, FString Payload) {
	if (!SendSocket) {
		UE_LOG(LogTemp, Warning, TEXT("no socket was available"))
		return false;
	}

	FRBGameSocketMessage Message;
	Message.Type = Type;
	Message.Payload = Base64Utilities::Base64Encode(Payload);

	FString Json = ToJsonString(Message);

	int32 BytesSent = 0;

	TCHAR* serializedChar = Json.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);

	bool success = SendSocket->SendTo((uint8*)TCHAR_TO_UTF8(serializedChar), size, BytesSent, *SocketConfig.GetRemoteAddr());
	if (success) {
		//UE_LOG(LogTemp, Warning, TEXT("Sent message: %s : was success: %s"), *Json, (success ? TEXT("true") : TEXT("false")))
		return true;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed sending message"))
		return false;
	}
}

void URBGameSocket::HandleControlMessage(FRBGameSocketMessage Message) {
	FString DecodedPayload = Base64Utilities::Base64Decode(Message.Payload);
	// received ping. send back the timestamp as pong.
	if (Message.Type == 0) {
		FPingMessage PingMessage;
		FromJson(DecodedPayload, &PingMessage);
		FPongMessage PongMessage;
		PongMessage.OriginTimestamp = PingMessage.OriginTimestamp;
		SendControlMessage(1, PongMessage.ToJson());
	}
	// received pong. fold this into the network statistics.
	else if (Message.Type == 1) {
		FPongMessage PongMessage;
		FromJson(DecodedPayload, &PongMessage);
		NetworkMonitor->HandlePong(PongMessage);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Unhandled message type: %d"), Message.Type)
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

void URBGameSocket::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	ReceivePendingMessages();
}
