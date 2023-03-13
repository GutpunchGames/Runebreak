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
    FSerializedSimulation SerializedSimulation;
    SerializedSimulation.NumEntities = Entities.Num();
    int i = 0;
    for (auto& Entry : Entities) {
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

    TSet<int32> KeepEntities;
    for (int i = 0; i < SerializedSimulation.NumEntities; i++) {
        int32 EntityId = SerializedSimulation.Entities[i].EntityId;
        KeepEntities.Add(EntityId);
        USimulationEntity** ExistingEntity = (Entities.Find(EntityId));
        if (ExistingEntity) {
			(*(ExistingEntity))->SimDeserialize(SerializedSimulation.Entities[i]);
        }
        else {
            // todo: spawn the entity we need
            UE_LOG(LogTemp, Warning, TEXT("FAILED TO FIND ENTITY TO DESERIALIZE. SPAWNING ONE INSTEAD"))
			TSubclassOf<USimulationEntity> RuntimeClass = SerializedSimulation.Entities[i].EntityClass;
			USimulationEntity* Entity = NewObject<USimulationEntity>(this, RuntimeClass);
			Entity->SimDeserialize(SerializedSimulation.Entities[i]);
            AddEntityToSimulation(Entity);
        }
    }

    // delete unused entities
    for (TMap<int32, USimulationEntity*>::TIterator Iterator = Entities.CreateIterator(); Iterator; ++Iterator) {
        if (!KeepEntities.Contains(Iterator.Key())) {
            Iterator.RemoveCurrent();
        }
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
