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

void URBGameSimulation::Update(int inputs[], int disconnect_flags)
{
    _framenumber++;
    _inputs[0] = inputs[0];
    _inputs[1] = inputs[1];

    for (int i = 0; i < NumEntities; i++) {
        Entities[i]->SimulationTick(this);
    }
}

URBPlayer* URBGameSimulation::GetPlayer(int PlayerId) {
    for (int i = 0; i < NumEntities; i++) {
        USimulationEntity* Entity = Entities[i];
        if (Entity->Id == PlayerId) {
			URBPlayer* Player = static_cast<URBPlayer*>(Entities[i]);
            return Player;
        }
    }

    URBPlayer* FAILURE = NewObject<URBPlayer>(this, "Failure Player");
    FAILURE->State.Position.y = 100;
    return FAILURE;
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

// this is all placeholder/debug for now...
UFUNCTION(BlueprintCallable)
USimulationEntity* URBGameSimulation::SpawnEntity(UClass* EntityClassIN, int DebugPlayerIndex) {
    int32 Id = EntityIdGenerator++;

    FPosition pos;
    pos.x = 0;
    pos.y = 0;

    USimulationEntity* Entity = NewObject<USimulationEntity>(this, EntityClassIN);
    Entity->Id = Id;

    // for now, just hardcode spawning players
    URBPlayer* Player = Cast<URBPlayer>(Entity);
	Player->State.Position = pos;

    if (DebugPlayerIndex == 0) {
        Player->State.Position.x = -100;
        Player->State.PlayerIndex = 0;
    }
    else if (DebugPlayerIndex == 1) {
        Player->State.Position.x = 100;
        Player->State.PlayerIndex = 1;
    }

	Entities.Emplace(Entity);
    NumEntities++;

    return Entity;
}

