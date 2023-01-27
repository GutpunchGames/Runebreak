#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NetworkStatistics.h"
#include "NetworkMonitor.h"
#include <RunebreakGame/Public/GameOrchestrator/GameSocket/RBGameSocket.h>
#include "ConnectionInfoWidget.generated.h"

UCLASS(Blueprintable)
class RUNEBREAKGAME_API UConnectionInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AverageRoundTripTimeDisplay;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PacketLossDisplay;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* MostRecentRemoteFrameDisplay;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* RemoteEndpointDisplay;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LocalPortDisplay;

	UFUNCTION()
	void SetNetworkStatistics(FNetworkStatistics NetworkStatistics);

	UFUNCTION(BlueprintCallable)
	void Bind(ARBGameSocket* GameSocket);

protected:
	virtual void NativeConstruct() override;
	UNetworkMonitor* BoundNetworkMonitor;
};
