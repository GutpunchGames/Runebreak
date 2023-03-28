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
	Player->Position.x = 150;
	Player->Position.y = 300;
	Player->State.PlayerIndex = 0;

	GameSimulationSerializer Serializer;
	Player->SerializeToBuffer(&Serializer);
	GameSimulationDeserializer Deserializer;
	Deserializer.Buffer = Serializer.Buffer;
	Player2->DeserializeFromBuffer(&Deserializer);

	TestEqual("Player id deserialized", Player2->Id, 5);
	TestTrue("Player state deserialized", Player->State == Player2->State);

	Player->RemoveFromRoot();
	Player2->RemoveFromRoot();
	return true;
}

bool FStringSerializationTest::RunTest(FString const& Parameters) {
	return true;
}

bool FStringSerializationTest2::RunTest(FString const& Parameters) {
	return true;
}

bool FStringSerializationTest3::RunTest(FString const& Parameters) {
	FString Value = "Test";
	GameSimulationSerializer Serializer;
	Serializer.WriteString(Value);
	GameSimulationDeserializer Deserializer;
	Deserializer.Buffer = Serializer.Buffer;
	FString OutValue = Deserializer.ReadString();
	TestEqual("Got correct value", OutValue, "Test");
	return true;
}

bool FStringSerializationTest4::RunTest(FString const& Parameters) {
	FString Value = "Poop";
	GameSimulationSerializer Serializer;
	Serializer.WriteString(Value);
	GameSimulationDeserializer Deserializer;
	Deserializer.Buffer = Serializer.Buffer;
	FString OutValue = Deserializer.ReadString();
	TestEqual("Got correct value", OutValue, "Poop");
	return true;
}

bool FStringSerializationTest5::RunTest(FString const& Parameters) {
	FString Value = "Poop";
	GameSimulationSerializer Serializer;
	Serializer.WriteString(Value);
	GameSimulationDeserializer Deserializer;
	Deserializer.Buffer = Serializer.Buffer;
	FString OutValue = Deserializer.ReadString();
	TestEqual("Got correct value", OutValue, "Poop");
	return true;
}

bool FStringSerializationTest6::RunTest(FString const& Parameters) {
	FString Value = "Poop";
	GameSimulationSerializer Serializer;
	Serializer.WriteString(Value);
	GameSimulationDeserializer Deserializer;
	Deserializer.Buffer = Serializer.Buffer;
	FString OutValue = Deserializer.ReadString();
	TestEqual("Got correct value", OutValue, "Poop");
	return true;
}

bool FStringSerializationTest7::RunTest(FString const& Parameters) {
	FString Value = "Poop";
	GameSimulationSerializer Serializer;
	Serializer.WriteString(Value);
	GameSimulationDeserializer Deserializer;
	Deserializer.Buffer = Serializer.Buffer;
	FString OutValue = Deserializer.ReadString();
	TestEqual("Got correct value", OutValue, "Poop");
	return true;
}
