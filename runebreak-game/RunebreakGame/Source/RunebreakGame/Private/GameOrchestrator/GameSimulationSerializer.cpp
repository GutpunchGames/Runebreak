#include "GameOrchestrator/GameSimulationSerializer.h"
#include "GameOrchestrator/RBGameSimulation.h"
#include "GameOrchestrator/Checksum.h"

bool GameSimulationSerializer::Serialize(URBGameSimulation* Simulation, unsigned char** buffer, int32* len, int32* checksum) {
    Size = 0;
    WriteInt(Simulation->_framenumber);
    WriteInt(Simulation->EntityIdGenerator);

    for (auto& Entry : Simulation->Entities) {
        Entry.Value->SerializeToBuffer(this);
		UE_LOG(LogTemp, Warning, TEXT("Serialized entity with id: %d, current buffer len: %d"), Entry.Value->Id, *len)
    }

    *len = Size;
    *buffer = (unsigned char*)malloc(*len);
    memcpy(*buffer, Buffer, *len);
    *checksum = fletcher32_checksum(*buffer, *len);
    UE_LOG(LogTemp, Warning, TEXT("Saved game with len: %d and checksum: %d"), *len, *checksum)
    return true;
}

bool GameSimulationDeserializer::Deserialize(URBGameSimulation* Simulation, unsigned char* buffer, int32 len) {
    Buffer = buffer;
    Cursor = 0;
    int32 Checksum = fletcher32_checksum(Buffer, len);
    UE_LOG(LogTemp, Warning, TEXT("Loading game with checksum: %d and len: %d"), Checksum, len)

	ReadInt(&(Simulation->_framenumber));
	ReadInt(&(Simulation->EntityIdGenerator));

	UE_LOG(LogTemp, Warning, TEXT("Got frame number: %d and ID generator: %d"), Simulation->_framenumber, Simulation->EntityIdGenerator)

    // for debug testing purposes, just empty all entities, always.
    // todo: keep them around and resolve entity matches during deserialization.
    Simulation->Entities.Empty();
    while (Cursor < len) {
        UE_LOG(LogTemp, Warning, TEXT("Reading entity at cursor: %d"), Cursor)
        int32 EntityBeginningCursor = Cursor;

        int32 EntityId;
        TSubclassOf<USimulationEntity> EntityClass;

        ReadInt(&EntityId);
        ReadBytes(&EntityClass, sizeof(EntityClass));
        UE_LOG(LogTemp, Warning, TEXT("Got entity id: %d. Cursor: %d. Class: %s"), EntityId, Cursor, *(EntityClass->GetName()))

        Cursor = EntityBeginningCursor;

		USimulationEntity* Entity = NewObject<USimulationEntity>(Simulation, EntityClass);
        Entity->SetupStates();
        int32 BytesRead = 0;
		Entity->DeserializeFromBuffer(this);
        Cursor += BytesRead;
		Simulation->AddEntityToSimulation(Entity);
    }

    return true;
}

void GameSimulationSerializer::WriteInt(const int32 Value) {
    memcpy(Buffer + Size, &Value, sizeof(Value));
    Size += sizeof(Value);
}

void GameSimulationSerializer::WriteBytes(void* Bytes, int32 NumBytes) {
    memcpy(Buffer + Size, Bytes, NumBytes);
    Size += NumBytes;
}

template <typename T> void GameSimulationSerializer::WriteClass(TSubclassOf<T> Class) {
    memcpy(Buffer + Size, &Class, sizeof(Class));
    Size += sizeof(Class);
}

void GameSimulationSerializer::WriteString(FString& Value) {
    uint8 OutBytes[32];
    int32 NumBytes = StringToBytes(Value, OutBytes, 32);
    UE_LOG(LogTemp, Warning, TEXT("Writing string with length: %d"), NumBytes)
    WriteInt(NumBytes);
	WriteBytes(OutBytes, NumBytes);
}

void GameSimulationSerializer::WriteRawClass(UClass Class) {
    memcpy(Buffer + Size, &Class, sizeof(Class));
    Size += sizeof(Class);
}

void GameSimulationDeserializer::ReadInt(int32* Destination) {
    memcpy(Destination, Buffer + Cursor, sizeof(int32));
    Cursor += sizeof(int32);
}

void GameSimulationDeserializer::ReadBytes(void* Destination, int32 NumBytes) {
    memcpy(Destination, Buffer + Cursor, NumBytes);
    Cursor += NumBytes;
}

void GameSimulationDeserializer::ReadRawClass(UClass* Destination) {
    memcpy(Destination, Buffer + Cursor, sizeof(UClass));
    Cursor += sizeof(UClass);
}

template <typename T> void GameSimulationDeserializer::ReadClass(TSubclassOf<T>* Destination) {
    memcpy(Destination, Buffer + Cursor, sizeof(TSubclassOf<T>));
    Cursor += sizeof(TSubclassOf<T>);
}

FString GameSimulationDeserializer::ReadString() {
    int32 NumBytes;
    ReadInt(&NumBytes);
    ReadBytes(ReadBuffer, NumBytes);
    FString Result = BytesToString(ReadBuffer, NumBytes);
	return Result;
}
