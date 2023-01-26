#include "GameOrchestrator/GameSocket/ConnectionInfoWidget.h"

void UConnectionInfoWidget::NativeConstruct() {

}

void UConnectionInfoWidget::SetNetworkStatistics(FNetworkStatistics NetworkStatistics) {
	FString RTT_Str = FString::Printf(TEXT("%f ms"), NetworkStatistics.AverageRoundTripTime);
	AverageRoundTripTimeDisplay->SetText(FText::FromString(RTT_Str));
}

void UConnectionInfoWidget::Bind(ARBGameSocket* GameSocket) {
	if (GameSocket == nullptr) {
		return;
	}

	if (GameSocket->NetworkMonitor != nullptr) {
		BoundNetworkMonitor = GameSocket->NetworkMonitor;
		GameSocket->NetworkMonitor->OnNetworkStatisticsChangedDelegate.AddUObject(this, &UConnectionInfoWidget::SetNetworkStatistics);

		FRBGameSocketConfig GameSocketConfig = GameSocket->SocketConfig;
		FString RemoteEndpointStr = FString::Printf(TEXT("%s:%d"), *GameSocketConfig.UDPSocketConfig.RemoteHost, GameSocketConfig.UDPSocketConfig.RemotePort);
		RemoteEndpointDisplay->SetText(FText::FromString(RemoteEndpointStr));

		FString LocalPortStr = FString::Printf(TEXT(":%d"), GameSocketConfig.UDPSocketConfig.LocalPort);
		LocalPortDisplay->SetText(FText::FromString(LocalPortStr));
	}
}
