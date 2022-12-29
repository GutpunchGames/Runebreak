#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChatMessage.generated.h"

USTRUCT()
struct FChatMessage
{
	GENERATED_BODY()

	UPROPERTY()
		FString authorId;
	UPROPERTY()
		FString authorName;
	UPROPERTY()
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
