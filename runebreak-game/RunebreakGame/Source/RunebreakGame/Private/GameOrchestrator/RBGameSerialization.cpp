#include "GameOrchestrator/RBGameSerialization.h"
#include "GameOrchestrator/Checksum.h"

int32 FSerializedEntity::ComputeChecksum() { 
    return fletcher32_checksum(Bytes, Size);
}

int32 FSerializedSimulation::ComputeChecksum() {
    int32 Checksum = 0;
    for (int i = 0; i < NumEntities; i++) {
        Checksum += Entities[i].ComputeChecksum();
    }

    return Checksum;
}
