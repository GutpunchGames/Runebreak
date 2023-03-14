#include "GameOrchestrator/RBGameSimulation.h"
#include "GameOrchestrator/Checksum.h"
#include "GameOrchestrator/RBInput.h"

void URBGameSimulation::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("Simulation START"))
    NumEntities = 0;
    EntityIdGenerator = 0;

    UE_LOG(LogTemp, Warning, TEXT("Simulation Init END"))
}

void URBGameSimulation::SimulationTick(int inputs[], int disconnect_flags)
{
    _framenumber++;
    _inputs[0] = inputs[0];
    _inputs[1] = inputs[1];

    TArray<int32> Keys;
    Entities.GenerateKeyArray(Keys);
    for (auto& Key : Keys) {
        // move, update hitboxes, etc.
        Entities[Key]->Act(this);
    }

    for (auto& Entry : Entities) {
        // consume hitboxes.
        Entry.Value->ResolveCollisions(this);
    }
}

bool URBGameSimulation::Save(unsigned char** buffer, int32* len, int32* checksum)
{
    *len = 0;
    for (auto& Entry : Entities) {
        int32 BytesWritten = 0;
        Entry.Value->SerializeToBuffer(GameStateBuffer + *len, &BytesWritten);
        *len += BytesWritten;
		UE_LOG(LogTemp, Warning, TEXT("Serialized entity with id: %d, current buffer len: %d"), Entry.Value->Id, GameStateBufferLen)
    }
    *buffer = (unsigned char*)malloc(*len);
    memcpy(*buffer, GameStateBuffer, *len);
    *checksum = fletcher32_checksum(*buffer, *len);
    UE_LOG(LogTemp, Warning, TEXT("Saved game with len: %d and checksum: %d"), *len, *checksum)
    return true;
}

bool URBGameSimulation::Load(unsigned char* buffer, int32 len)
{
    int32 Checksum = fletcher32_checksum(buffer, len);
	UE_LOG(LogTemp, Warning, TEXT("Loading game with checksum: %d and len: %d"), Checksum, len)
    // for debug testing purposes, just empty all entities, always.
    // todo: keep them around and resolve entity matches during deserialization.
    Entities.Empty();
    int32 Cursor = 0;
    while (Cursor < len) {
        UE_LOG(LogTemp, Warning, TEXT("Starting peek w/ cursor position: %d"), Cursor)
        int32 PeekCursor = Cursor;
        int32 EntityId;
        TSubclassOf<USimulationEntity> EntityClass;

        UE_LOG(LogTemp, Warning, TEXT("Peeking entity id with cursor: %d"), PeekCursor)
        memcpy(&EntityId, buffer + PeekCursor, sizeof(EntityId));
        PeekCursor += sizeof(EntityId);
        UE_LOG(LogTemp, Warning, TEXT("Got entity id: %d"), EntityId)
        UE_LOG(LogTemp, Warning, TEXT("Peeking entity class with cursor: %d"), PeekCursor)
        memcpy(&EntityClass, buffer + PeekCursor, sizeof(EntityClass));
        UE_LOG(LogTemp, Warning, TEXT("Got entity class: %s"), *(EntityClass->GetName()))
        PeekCursor += sizeof(EntityClass);

        int32 BytesRead = 0;
		USimulationEntity* Entity = NewObject<USimulationEntity>(this, EntityClass);
		Entity->DeserializeFromBuffer(buffer + Cursor, &BytesRead);
        Cursor += BytesRead;
		AddEntityToSimulation(Entity);
    }

    return true;
}

USimulationEntity* URBGameSimulation::SpawnEntity(UClass* EntityClassIN) {
    int32 Id = EntityIdGenerator++;

    USimulationEntity* Entity = NewObject<USimulationEntity>(this, EntityClassIN);
    Entity->EntityClass = EntityClassIN;
    Entity->Id = Id;
    Entity->InitDefaults();

    AddEntityToSimulation(Entity);
    return Entity;
}

void URBGameSimulation::AddEntityToSimulation(USimulationEntity* Entity) {
    Entities.Add(Entity->Id, Entity);
}

bool URBGameSimulation::RemoveEntity(int32 EntityId) {
    return Entities.Remove(EntityId) > 0;
}
