#include "GameOrchestrator/RBGameSimulation.h"
#include "GameOrchestrator/Checksum.h"
#include "GameOrchestrator/RBInput.h"

void FRBGameSimulation::Init()
{
    FPosition pos;
    pos.x = 0;
    pos.y = 0;

    FRBPlayer* player1 = new FRBPlayer();
    player1->position = pos;
    player1->position.x = -100;
    player1->PlayerIndex = 0;
    player1->Id = 0;
    Entities[0] = player1;

    FRBPlayer* player2 = new FRBPlayer();
    player2->position = pos;
    player2->position.x = 100;
    player2->PlayerIndex = 1;
    player2->Id = 1;
    Entities[1] = player2;

    NumEntities = 2;
}

void FRBGameSimulation::Update(int inputs[], int disconnect_flags)
{
    _framenumber++;
    _inputs[0] = inputs[0];
    _inputs[1] = inputs[1];

    for (int i = 0; i < NumEntities; i++) {
        Entities[i]->SimulationTick(this);
    }
}

FRBPlayer* FRBGameSimulation::GetPlayer(int PlayerId) {
    for (int i = 0; i < NumEntities; i++) {
        FSimulationEntity* Entity = Entities[i];
        if (Entity->Id == PlayerId) {
			FRBPlayer* Player = static_cast<FRBPlayer*>(Entities[i]);
            return Player;
        }
    }

    FRBPlayer* FAILURE = new FRBPlayer();
    FAILURE->position.y = 100;
    return FAILURE;
}

bool FRBGameSimulation::Save(unsigned char** buffer, int32* len, int32* checksum)
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

bool FRBGameSimulation::Load(unsigned char* buffer, int32 len)
{
    FSerializedSimulation SerializedSimulation;
    memcpy(&SerializedSimulation, buffer, len);

    for (int i = 0; i < SerializedSimulation.NumEntities; i++) {
        Entities[i]->Deserialize(SerializedSimulation.Entities[i]);
    }
    return true;
}

