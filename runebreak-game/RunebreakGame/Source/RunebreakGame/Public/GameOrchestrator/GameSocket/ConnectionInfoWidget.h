#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NetworkStatistics.h"
#include "NetworkMonitor.h"
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

	UFUNCTION()
	void SetData(FNetworkStatistics NetworkStatistics);

	UFUNCTION(BlueprintCallable)
	void Bind(UNetworkMonitor* NetworkMonitor);

protected:
	virtual void NativeConstruct() override;
	UNetworkMonitor* BoundNetworkMonitor;
};
