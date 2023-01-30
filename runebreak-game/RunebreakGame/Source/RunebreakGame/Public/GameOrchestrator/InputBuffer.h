#pragma once

#include <RunebreakGame/Public/GameOrchestrator/Input.h>
#include "UObject/Interface.h"
#include "InputBuffer.generated.h"

UINTERFACE(MinimalAPI, meta = (Blueprintable))
class UInputBuffer : public UInterface
{
    GENERATED_BODY()
};

class IInputBuffer
{
    GENERATED_BODY()

public:
    virtual FInput GetInput(int Frame) { 
        return FInput();
    };
};