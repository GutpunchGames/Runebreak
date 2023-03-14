#include "SerializationTest.h"
#include "GameOrchestrator/RBPlayer.h"

bool FPlayerSerializationTest::RunTest(FString const& Parameters) {
	URBPlayer* Player = NewObject<URBPlayer>();
	URBPlayer* Player2 = NewObject<URBPlayer>();

	Player->AddToRoot();
	Player2->AddToRoot();

	Player->State.MoveSpeed = 20;
	Player->State.Position.x = 150;
	Player->State.Position.y = 300;
	Player->State.PlayerIndex = 0;

	FSerializedEntity SerializedEntity = Player->SimSerialize();
	Player2->SimDeserialize(SerializedEntity);

	TestTrue("Player deserialized properly", Player->State == Player2->State);

	Player->RemoveFromRoot();
	Player2->RemoveFromRoot();
	return true;
}

