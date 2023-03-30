#include "GameOrchestrator/RBGameSimulation.h"
#include "GameOrchestrator/Checksum.h"
#include "GameOrchestrator/RBInput.h"

void URBGameSimulation::Init()
{
    DetectionBoxes.AddDefaulted(MaxDetectionBoxes);
    for (auto& DetectionBox : DetectionBoxes) {
        DetectionBox.Type = DetectionBoxType::Inactive;
    }
}

void URBGameSimulation::SimulationTick(int inputs[], int disconnect_flags)
{
    NumActiveDetectionBoxes = 0;
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
    Entity->SetupStates(this);

    AddEntityToSimulation(Entity);
    return Entity;
}

void URBGameSimulation::AddEntityToSimulation(USimulationEntity* Entity) {
    Entities.Add(Entity->Id, Entity);
}

bool URBGameSimulation::RemoveEntity(int32 EntityId) {
    return Entities.Remove(EntityId) > 0;
}

void URBGameSimulation::ActivateDetectionBox(int32 OwnerId, int32 PosX, int32 PosY, int32 SizeX, int32 SizeY, DetectionBoxType Type) {
    DetectionBoxes[NumActiveDetectionBoxes].OwnerId = OwnerId;
    DetectionBoxes[NumActiveDetectionBoxes].Position.x = PosX;
    DetectionBoxes[NumActiveDetectionBoxes].Position.y = PosY;
    DetectionBoxes[NumActiveDetectionBoxes].Size.X = SizeX;
    DetectionBoxes[NumActiveDetectionBoxes].Size.Y = SizeY;
    DetectionBoxes[NumActiveDetectionBoxes].Type = Type;

    NumActiveDetectionBoxes++;

    if (NumActiveDetectionBoxes >= MaxDetectionBoxes) {
        UE_LOG(LogTemp, Fatal, TEXT("exceeded max detection boxes for tick"))
    }
}
