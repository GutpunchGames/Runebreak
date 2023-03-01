#include "GameOrchestrator/RBInput.h"
#include "GameOrchestrator/RBPlayerController.h"

int32 ARBPlayerController::GetPlayerInput()
{
    static const struct {
        FKey     key;
        int32    input;
    } inputtable[] = {
       { EKeys::Up,       INPUT_MOVE_UP },
       { EKeys::Down,     INPUT_MOVE_DOWN },
    };
    int32 i, inputs = 0;

    for (i = 0; i < sizeof(inputtable) / sizeof(inputtable[0]); i++) {
        if (IsInputKeyDown(inputtable[i].key)) {
            inputs |= inputtable[i].input;
        }
    }

    return inputs;
}
