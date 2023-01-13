#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChatMessage.generated.h"

USTRUCT(BlueprintType)
struct FChatMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		FString authorId;
	UPROPERTY(BlueprintReadOnly)
		FString authorName;
	UPROPERTY(BlueprintReadOnly)
		FString text;

	FChatMessage() {}

	FChatMessage(FString _authorId, FString _authorName, FString _text) {
		authorId = _authorId;
		authorName = _authorName;
		text = _text;
	}

	FString ToString() {
		return FString(
			+ "\tauthorId: " + authorId + "\n"
			+ "\tauthorName: " + authorName + '\n'
			+ "\ttext: " + text + '\n'
		);
	}
};
