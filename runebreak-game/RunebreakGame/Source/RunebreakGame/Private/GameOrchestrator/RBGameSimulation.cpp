#include "GameOrchestrator/RBGameSimulation.h"
#include "GameOrchestrator/Checksum.h"
#include "GameOrchestrator/RBInput.h"

void URBGameSimulation::Init()
{
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
    return Serializer.Serialize(this, buffer, len, checksum);
}

bool URBGameSimulation::Load(unsigned char* buffer, int32 len)
{
    if (!Deserializer.Deserialize(this, buffer, len)) {
        UE_LOG(LogTemp, Fatal, TEXT("Failed to load from buffer"))
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
