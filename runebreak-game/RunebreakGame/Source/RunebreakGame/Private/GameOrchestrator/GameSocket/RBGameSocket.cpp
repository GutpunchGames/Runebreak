#include "GameOrchestrator/GameSocket/RBGameSocket.h"
#include "GameOrchestrator/GameSocket/InputsMessage.h"
#include <RunebreakGame/Public/RBGameSession/Utilities/JsonUtils.h>
#include "Kismet/KismetStringLibrary.h"
#include <Utilities/TimeUtilities.h>
#include <Utilities/Base64Utilities.h>

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
	Socket = NewObject<UUDPSocket>(this, "UDPSocket");

	Socket->Setup(SocketConfig.UDPSocketConfig);
	Socket->OnBytesReceivedDelegate.BindUObject(this, &URBGameSocket::HandleMessage);

	NetworkMonitor = NewObject<UNetworkMonitor>(this, TEXT("NetworkMonitor"));
	NetworkMonitor->PingImpl = [this](FPingMessage PingMessage) {
		SendControlMessage(MESSAGE_TYPE_PING, PingMessage.ToJson());
	};

	GetWorld()->GetTimerManager().SetTimer(PingTimerHandle, NetworkMonitor, &UNetworkMonitor::DoPing, PingIntervalSeconds, true);
}

void URBGameSocket::ReceivePendingMessages() {
	if (Socket) {
		Socket->ReceivePendingMessages();
	}
}

void URBGameSocket::SendControlMessage(int Type, FString Payload) {
	if (SocketConfig.LogToScreen) {
		FString LogMessage = FString::Printf(TEXT("SEND: %d -- %s"), Type, *Payload);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Red, *LogMessage, /*newer on top*/ true);
	}

	FRBGameSocketMessage Message;
	Message.Type = Type;
	Message.Payload = Base64Utilities::Base64Encode(Payload);

	FString Json = ToJsonString(Message);
	Socket->SendMessage(Json);
}

void URBGameSocket::HandleMessage(const FString& Bytes) {
	FRBGameSocketMessage Message;
	FromJson<FRBGameSocketMessage>(Bytes, &Message);
	FString DecodedPayload = Base64Utilities::Base64Decode(Message.Payload);

	if (SocketConfig.LogToScreen) {
		FString LogMessage = FString::Printf(TEXT("RECV: %d -- %s"), Message.Type, *DecodedPayload);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Red, *LogMessage, /*newer on top*/ true);
	}

	// received ping. send back the timestamp as pong.
	if (Message.Type == MESSAGE_TYPE_PING) {
		FPingMessage PingMessage;
		FromJson(DecodedPayload, &PingMessage);
		FPongMessage PongMessage;
		PongMessage.OriginTimestamp = PingMessage.OriginTimestamp;
		SendControlMessage(MESSAGE_TYPE_PONG, PongMessage.ToJson());
	}
	// received pong. fold this into the network statistics.
	else if (Message.Type == MESSAGE_TYPE_PONG) {
		FPongMessage PongMessage;
		FromJson(DecodedPayload, &PongMessage);
		NetworkMonitor->HandlePong(PongMessage);
	}
	else if (Message.Type == MESSAGE_TYPE_INPUTS) {
		FInputsMessage InputsMessage;
		FInputsMessage::ParseString(DecodedPayload, InputsMessage);
		OnInputsReceivedDelegate.ExecuteIfBound(InputsMessage);
		UE_LOG(LogTemp, Warning, TEXT("Got inputs message: %s"), *InputsMessage.ToString())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Unhandled message type: %d"), Message.Type)
	}
}

void URBGameSocket::Teardown() {
	GetWorld()->GetTimerManager().ClearTimer(PingTimerHandle);
	if (Socket) {
		Socket->Teardown();
	}
}

void URBGameSocket::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	ReceivePendingMessages();
}
