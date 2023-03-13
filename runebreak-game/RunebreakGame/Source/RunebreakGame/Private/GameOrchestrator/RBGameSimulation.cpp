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

    for (auto& Entity : Entities) {
        // move, update hitboxes, etc.
        Entity->Act(this);
    }

    for (auto& Entity : Entities) {
        // comsume hitboxes.
        Entity->ResolveCollisions(this);
    }
}

bool URBGameSimulation::Save(unsigned char** buffer, int32* len, int32* checksum)
{
    FSerializedSimulation SerializedSimulation;
    SerializedSimulation.NumEntities = NumEntities;
    for (int i = 0; i < NumEntities; i++) {
        SerializedSimulation.Entities[i] = Entities[i]->Serialize();
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
        Entities[i]->Deserialize(SerializedSimulation.Entities[i]);
    }
    return true;
}

USimulationEntity* URBGameSimulation::SpawnEntity(UClass* EntityClassIN) {
    int32 Id = EntityIdGenerator++;

    USimulationEntity* Entity = NewObject<USimulationEntity>(this, EntityClassIN);
    Entity->Id = Id;
    Entity->InitDefaults();

	Entities.Emplace(Entity);
    NumEntities++;

    return Entity;
}

