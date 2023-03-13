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

    for (auto& Entry : EntityIndex) {
        // move, update hitboxes, etc.
        Entry.Value->Act(this);
    }

    for (auto& Entry : EntityIndex) {
        // comsume hitboxes.
        Entry.Value->ResolveCollisions(this);
    }
}

bool URBGameSimulation::Save(unsigned char** buffer, int32* len, int32* checksum)
{
    FSerializedSimulation SerializedSimulation;
    SerializedSimulation.NumEntities = EntityIndex.Num();
    int i = 0;
    for (auto& Entry : EntityIndex) {
        SerializedSimulation.Entities[i] = Entry.Value->SimSerialize();
        i++;
    }
    *len = sizeof(SerializedSimulation);
    *buffer = (unsigned char*) malloc(*len);
    if (!*buffer) {
        return false;
    }
    memcpy(*buffer, &SerializedSimulation, *len);
    *checksum = SerializedSimulation.ComputeChecksum();
    return true;
}

bool URBGameSimulation::Load(unsigned char* buffer, int32 len)
{
    FSerializedSimulation SerializedSimulation;
    memcpy(&SerializedSimulation, buffer, len);

    for (int i = 0; i < SerializedSimulation.NumEntities; i++) {
        int32 EntityId = SerializedSimulation.Entities[i].EntityId;
        USimulationEntity** ExistingEntity = (EntityIndex.Find(EntityId));
        if (ExistingEntity) {
			(*(ExistingEntity))->SimDeserialize(SerializedSimulation.Entities[i]);
        }
        else {
            // todo: spawn the entity we need
            UE_LOG(LogTemp, Warning, TEXT("FAILED TO FIND ENTITY TO DESERIALIZE"))
        }
    }
    return true;
}

USimulationEntity* URBGameSimulation::SpawnEntity(UClass* EntityClassIN) {
    int32 Id = EntityIdGenerator++;

    USimulationEntity* Entity = NewObject<USimulationEntity>(this, EntityClassIN);
    Entity->Id = Id;
    Entity->InitDefaults();

    EntityIndex.Add(Entity->Id, Entity);

    return Entity;
}

bool URBGameSimulation::RemoveEntity(int32 EntityId) {
    return EntityIndex.Remove(EntityId) > 0;
}
