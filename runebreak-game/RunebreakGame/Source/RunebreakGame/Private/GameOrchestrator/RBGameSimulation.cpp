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

void FSimulationEntity::SimulationTick(FRBGameSimulation* Simulation) { }
FSerializedEntity FSimulationEntity::Serialize() { 
    FSerializedEntity result;
    result.EntityType = -1;
    result.Size = 0;
    return result;
}

int32 FSerializedEntity::ComputeChecksum() { 
    return fletcher32_checksum(Bytes, Size);
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

int32 FSerializedSimulation::ComputeChecksum() {
    int32 Checksum = 0;
    for (int i = 0; i < NumEntities; i++) {
        Checksum += Entities[i].ComputeChecksum();
    }

    return Checksum;
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

void FSimulationEntity::Deserialize(FSerializedEntity SerializedEntity) { }

FSerializedEntity FRBPlayer::Serialize() {
    FSerializedEntity result;
    result.EntityType = 0;
    result.Size = sizeof(*this);
    memcpy(result.Bytes, this, result.Size);
    return result;
}

void FRBPlayer::Deserialize(FSerializedEntity SerializedEntity) {
    memcpy(this, SerializedEntity.Bytes, SerializedEntity.Size);
}

void FRBPlayer::SimulationTick(FRBGameSimulation* Simulation) {
    if (!Simulation) {
        UE_LOG(LogTemp, Warning, TEXT("BAD SIM"))
        return;
    }
    int Inputs = Simulation->_inputs[PlayerIndex];
    int MoveUp = Inputs & INPUT_MOVE_UP;
    int MoveDown = Inputs & INPUT_MOVE_DOWN;
    if (MoveUp) {
		position.y = position.y + 10;
    }
    else if (MoveDown) {
		position.y = position.y - 10;
    }
};
