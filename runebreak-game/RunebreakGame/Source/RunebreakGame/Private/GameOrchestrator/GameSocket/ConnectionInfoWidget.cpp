#include "GameOrchestrator/GameSocket/ConnectionInfoWidget.h"

void UConnectionInfoWidget::NativeConstruct() {

}

void UConnectionInfoWidget::SetData(FNetworkStatistics NetworkStatistics) {
	FString RTT_Str = FString::Printf(TEXT("%f ms"), NetworkStatistics.AverageRoundTripTime);
	AverageRoundTripTimeDisplay->SetText(FText::FromString(RTT_Str));
}

void UConnectionInfoWidget::Bind(UNetworkMonitor* NetworkMonitor) {
	BoundNetworkMonitor = NetworkMonitor;
	NetworkMonitor->OnNetworkStatisticsChangedDelegate.AddUObject(this, &UConnectionInfoWidget::SetData);
}
