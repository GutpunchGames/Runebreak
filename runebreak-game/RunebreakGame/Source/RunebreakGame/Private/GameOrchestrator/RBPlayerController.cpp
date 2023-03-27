#include "GameOrchestrator/RBPlayerController.h"
#include "GameOrchestrator/RBInput.h"

int32 ARBPlayerController::GetPlayerInput()
{
    static const struct {
        FKey     key;
        int32    input;
    } inputtable[] = {
       { EKeys::Left,       INPUT_MOVE_LEFT },
       { EKeys::Right,     INPUT_MOVE_RIGHT },
       { EKeys::A,     INPUT_SHOOT },
    };

    int32 i, inputs = 0;
    for (i = 0; i < sizeof(inputtable) / sizeof(inputtable[0]); i++) {
        if (IsInputKeyDown(inputtable[i].key)) {
            inputs |= inputtable[i].input;
        }
    }

    return inputs;
}
