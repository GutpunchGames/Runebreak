// Copyright 2020 BwdYeti.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GGPOGameInstance.generated.h"

// Forward declarations
class UGGPONetwork;

/**
 * 
 */
UCLASS()
class GGPOUE4_API UGGPOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UGGPONetwork* GGPONetwork;

    /** Creates a collection of network addresses. */
    UFUNCTION(BlueprintCallable, Category = "GGPO")
        void CreateNetwork(TSet<int32> LocalPlayerIndices, int32 LocalPort, FString RemoteAddress);

    /** Creates a network for a sync test.*/
    UFUNCTION(BlueprintCallable, Category = "GGPO")
        void CreateSyncTestNetwork();
};
