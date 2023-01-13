#pragma once

#include "UObject/NoExportTypes.h"
#include "UserTypes.generated.h"

USTRUCT(BlueprintType)
struct FUser
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly)
		FString username;
	UPROPERTY(BlueprintReadOnly)
		FString userId;

	FString ToString() {
		return FString(
			+"\tusername: " + username + "\n"
			+ "\tuserId: " + userId + "\n"
		);
	}
};
