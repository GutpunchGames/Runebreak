#include "GameOrchestrator/GameSocket/RBGameSocket.h"
#include "GameOrchestrator/GameSocket/InputsMessage.h"
#include <RunebreakGame/Public/RBGameSession/Utilities/JsonUtils.h>
#include "Kismet/KismetStringLibrary.h"
#include <Utilities/TimeUtilities.h>
#include <Utilities/Base64Utilities.h>

ARBGameSocket::ARBGameSocket()
{
	SocketState = ERBGameSocketState::Uninitialized;
	IsSetup = false;

	CurrentFrame = 0;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

ARBGameSocket::~ARBGameSocket()
{
}

void ARBGameSocket::Setup() {
	UE_LOG(LogTemp, Warning, TEXT("Setup Socket"))
	Socket = NewObject<UUDPSocket>(this, TEXT("UDPSocket"));
	NetworkMonitor = NewObject<UNetworkMonitor>(this, TEXT("NetworkMonitor"));

	Socket->Setup(SocketConfig.UDPSocketConfig);
	Socket->OnBytesReceivedDelegate.BindUObject(this, &ARBGameSocket::HandleMessage);

	IsSetup = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
}

void ARBGameSocket::ReceivePendingMessages() {
	if (IsSetup && Socket) {
		Socket->ReceivePendingMessages();
	}
}

void ARBGameSocket::SendPing(int LocalFrame) {
	int64 CurrentTime = TimeUtilities::GetMillisSinceEpoch();

	FPingMessage PingMessage;
	PingMessage.OriginTimestamp = FString::Printf(TEXT("%lld"), CurrentTime);
	PingMessage.OriginFrame = LocalFrame;

	SendControlMessage(MESSAGE_TYPE_PING, ToJsonString(PingMessage));
}

void ARBGameSocket::SendControlMessage(int Type, FString Payload) {
	if (SocketConfig.LogToScreen) {
		FString LogMessage = FString::Printf(TEXT("SEND: %d -- %s"), Type, *Payload);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3, FColor::Green, *LogMessage, /*newer on top*/ true);
	}

	FRBGameSocketMessage Message;
	Message.Type = Type;
	Message.Payload = Base64Utilities::Base64Encode(Payload);

	FString Json = ToJsonString(Message);
	Socket->SendMessage(Json);
}

void ARBGameSocket::HandleMessage(const FString& Bytes) {
	FRBGameSocketMessage Message;
	FromJson<FRBGameSocketMessage>(Bytes, &Message);
	FString DecodedPayload = Base64Utilities::Base64Decode(Message.Payload);

	if (SocketConfig.LogToScreen) {
		FString LogMessage = FString::Printf(TEXT("RECV: %d -- %s"), Message.Type, *DecodedPayload);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3, FColor::Red, *LogMessage, /*newer on top*/ true);
	}

	// received ping. send back the timestamp as pong.
	if (Message.Type == MESSAGE_TYPE_PING) {
		FPingMessage PingMessage;
		FromJson(DecodedPayload, &PingMessage);
		FPongMessage PongMessage;
		PongMessage.OriginTimestamp = PingMessage.OriginTimestamp;
		PongMessage.RemoteFrame = CurrentFrame;
		SendControlMessage(MESSAGE_TYPE_PONG, ToJsonString(PongMessage));
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

void ARBGameSocket::Teardown() {
	if (IsSetup && Socket) {
		Socket->Teardown();
	}
}

void ARBGameSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsSetup) {
		ReceivePendingMessages();
	}
}
