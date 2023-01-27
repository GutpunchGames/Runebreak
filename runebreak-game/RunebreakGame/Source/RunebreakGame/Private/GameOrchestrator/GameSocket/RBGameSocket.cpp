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

	PrimaryActorTick.bCanEverTick = false;
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
	IsSetup = true;
}

void ARBGameSocket::ReceivePendingMessages(FSyncMessage& LatestSyncMessage) {
	LatestSyncMessage.OriginFrame = -1;

	if (IsSetup) {
		uint32 Size;

		while (Socket->HasPendingData(Size)) {
			FString Bytes = Socket->ReceiveBytes(Size);
			FRBGameSocketMessage Message;
			FromJson<FRBGameSocketMessage>(Bytes, &Message);
			FString DecodedPayload = Base64Utilities::Base64Decode(Message.Payload);

			LogRecv(Message.Type, DecodedPayload);

			if (Message.Type == MESSAGE_TYPE_SYNC) {
				FSyncMessage InSyncMessage;
				FromJson(DecodedPayload, &InSyncMessage);
				if (InSyncMessage.OriginFrame >= LatestSyncMessage.OriginFrame) {
					UE_LOG(LogTemp, Warning, TEXT("OVERWROTE LatestSyncMessage: md: %d"), InSyncMessage.LatestInput.MoveDirection)
					LatestSyncMessage = InSyncMessage;
				}
			}
			// received ping. send back the timestamp as pong.
			else if (Message.Type == MESSAGE_TYPE_PING) {
				FPingMessage PingMessage;
				FromJson(DecodedPayload, &PingMessage);
				FPongMessage PongMessage;
				PongMessage.OriginTimestamp = PingMessage.OriginTimestamp;
				SendControlMessage(MESSAGE_TYPE_PONG, ToJsonString(PongMessage));
			}
			// received pong. fold this into the network statistics.
			else if (Message.Type == MESSAGE_TYPE_PONG) {
				FPongMessage PongMessage;
				FromJson(DecodedPayload, &PongMessage);
				NetworkMonitor->HandlePong(PongMessage);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Unhandled message type: %d"), Message.Type)
			}
		}

		if (LatestSyncMessage.OriginFrame >= 0) {
			NetworkMonitor->HandleSync(LatestSyncMessage);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Final MD: %d -- OF: %d"), LatestSyncMessage.LatestInput.MoveDirection, LatestSyncMessage.OriginFrame)
}

void ARBGameSocket::SendPing(int LocalFrame) {
	int64 CurrentTime = TimeUtilities::GetMillisSinceEpoch();

	FPingMessage PingMessage;
	PingMessage.OriginTimestamp = FString::Printf(TEXT("%lld"), CurrentTime);

	SendControlMessage(MESSAGE_TYPE_PING, ToJsonString(PingMessage));
}

void ARBGameSocket::SendSync(const FSyncMessage& SyncMessage) {
	SendControlMessage(MESSAGE_TYPE_SYNC, ToJsonString(SyncMessage));
}

void ARBGameSocket::SendControlMessage(int Type, FString Payload) {
	if (SocketConfig.LogToScreen) {
		LogSend(Type, Payload);
	}

	FRBGameSocketMessage Message;
	Message.Type = Type;
	Message.Payload = Base64Utilities::Base64Encode(Payload);

	FString Json = ToJsonString(Message);
	Socket->SendMessage(Json);
}

void ARBGameSocket::Teardown() {
	if (IsSetup && Socket) {
		Socket->Teardown();
	}
}

void ARBGameSocket::LogSend(int Type, const FString& Payload) {
	UE_LOG(LogTemp, Warning, TEXT("SEND: %d -- %s"), Type, *Payload);
}

void ARBGameSocket::LogRecv(int Type, const FString& Payload) {
	UE_LOG(LogTemp, Warning, TEXT("RECV: %d -- %s"), Type, *Payload);
}
