#include "GameOrchestrator/RBGameSimulation.h"
#include "GameOrchestrator/Checksum.h"
#include "GameOrchestrator/RBInput.h"

void URBGameSimulation::Init()
{
    FPosition pos;
    pos.x = 0;
    pos.y = 0;

    URBPlayer* player1 = NewObject<URBPlayer>(this, "Player 1");
    player1->State.Position = pos;
    player1->State.Position.x = -100;
    player1->State.PlayerIndex = 0;
    player1->Id = 0;
    Entities[0] = player1;

    URBPlayer* player2 = NewObject<URBPlayer>(this, "Player 2");
    player2->State.Position = pos;
    player2->State.Position.x = 100;
    player2->State.PlayerIndex = 1;
    player2->Id = 1;
    Entities[1] = player2;

    NumEntities = 2;
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

