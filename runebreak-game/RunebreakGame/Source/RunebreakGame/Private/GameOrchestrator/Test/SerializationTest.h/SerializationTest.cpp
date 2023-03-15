#include "SerializationTest.h"
#include "GameOrchestrator/RBPlayer.h"
#include "GameOrchestrator/GameSimulationSerializer.h"

bool FPlayerSerializationTest::RunTest(FString const& Parameters) {
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

	GameSimulationSerializer Serializer;

	Player->SerializeToBuffer(&Serializer);

	//int32 BytesRead = 0;
	//Player2->DeserializeFromBuffer(Serializer.Buffer, &BytesRead);

	//TestEqual("Player id deserialized", Player2->Id, 5);
	//TestTrue("Player state deserialized", Player->State == Player2->State);

	Player->RemoveFromRoot();
	Player2->RemoveFromRoot();
	return true;
}

