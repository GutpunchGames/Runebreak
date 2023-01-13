#pragma once

#include "CoreMinimal.h"
#include "ConnectionStatus.generated.h"

UENUM()
enum class EConnectionStatus: uint8
{
	Uninitialized = 0x0,
	Connecting = 0x1,
	Connected = 0x2
};
