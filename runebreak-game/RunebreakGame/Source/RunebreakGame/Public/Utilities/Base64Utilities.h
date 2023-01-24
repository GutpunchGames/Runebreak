#pragma once

#include "CoreMinimal.h"
#include "Misc/Base64.h"

class Base64Utilities {
public:
	static FString Base64Encode(const FString& Source);
	static FString Base64Decode(const FString& Source);
};
