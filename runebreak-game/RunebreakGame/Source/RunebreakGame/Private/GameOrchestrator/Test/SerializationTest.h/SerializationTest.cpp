#include "SerializationTest.h"
#include "GameOrchestrator/RBPlayer.h"
#include "GameOrchestrator/SelfDestructiveEntity.h"

bool FPlayerSerializationTest3::RunTest(FString const& Parameters) {
	return true;
}

bool FPlayerSerializationTest5::RunTest(FString const& Parameters) {
	return true;
}

bool FPlayerSerializationTest6::RunTest(FString const& Parameters) {
	return true;
}

bool FPlayerSerializationTest7::RunTest(FString const& Parameters) {
	URBPlayer* Player = NewObject<URBPlayer>();
	URBPlayer* Player2 = NewObject<URBPlayer>();

	Player->AddToRoot();
	Player2->AddToRoot();

	Player->Id = 5;

	Player->EntityClass = URBPlayer::StaticClass();

	Player->State.MoveSpeed = 20;
	Player->State.Position.x = 150;
	Player->State.Position.y = 300;
	Player->State.PlayerIndex = 0;

	unsigned char Buffer[512];
	int32 BytesWritten = 0;
	Player->SerializeToBuffer(Buffer, &BytesWritten);

	int32 BytesRead = 0;
	Player2->DeserializeFromBuffer(Buffer, &BytesRead);

	int32 PeekCursor = 0;
	int32 EntityId;
	TSubclassOf<USimulationEntity> EntityClass;

	memcpy(&EntityId, Buffer + PeekCursor, sizeof(EntityId));
	PeekCursor += sizeof(EntityId);
	memcpy(&EntityClass, Buffer + PeekCursor, sizeof(EntityClass));
	PeekCursor += sizeof(EntityClass);

	TestEqual("Peeked id", EntityId, 5);
	TestTrue("Peeked entity class", EntityClass == Player->EntityClass);
	TestEqual("Player id deserialized", Player2->Id, 5);
	TestTrue("Player state deserialized", Player->State == Player2->State);

	Player->RemoveFromRoot();
	Player2->RemoveFromRoot();
	return true;
}

bool FPlayerSerializationTest2::RunTest(FString const& Parameters) {
	URBPlayer* Player = NewObject<URBPlayer>();
	URBPlayer* Player2 = NewObject<URBPlayer>();

	Player->AddToRoot();
	Player2->AddToRoot();

	Player->State.MoveSpeed = 20;
	Player->State.Position.x = 150;
	Player->State.Position.y = 300;
	Player->State.PlayerIndex = 0;

	unsigned char Buffer[512];
	int32 BytesWritten = 0;
	Player->SerializeToBuffer(Buffer, &BytesWritten);

	int32 BytesRead = 0;
	Player2->DeserializeFromBuffer(Buffer, &BytesRead);

	TestTrue("Player deserialized properly", Player->State == Player2->State);

	Player->RemoveFromRoot();
	Player2->RemoveFromRoot();
	return true;
}

