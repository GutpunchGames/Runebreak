#include "Collisions/DetectionBox.h"

// load from a data table all the detection boxes for every frame for this state.
FStateDetectionBoxConfig UDetectionBoxLoader::LoadDetectionBoxConfigs(int NumFrames, UDataTable* DataTable) {
	FStateDetectionBoxConfig Result;
	if (!DataTable) return Result;

	int32 Frame = 1;
	TArray<FFrameDetectionBoxConfig> FrameDetectionBoxes;
	FrameDetectionBoxes.AddDefaulted(NumFrames + 1);

	for (const auto& Iterator : DataTable->GetRowMap()) {
		FDetectionBoxDataTableRow* Row = (FDetectionBoxDataTableRow*)Iterator.Value;
		FDetectionBoxConfig BoxConfig;
		BoxConfig.Offset = Row->Offset;
		BoxConfig.Size = Row->Size;
		BoxConfig.Type = Row->Type;

		for (int i = Row->StartFrame; i < Row->StartFrame + Row->Duration; i++) {
			if (i > NumFrames) {
				UE_LOG(LogTemp, Fatal, TEXT("detection box would exceed state duration"))
			}

			FrameDetectionBoxes[i].DetectionBoxes.Add(BoxConfig);
		}
	}

	Result.DetectionBoxesByFrame = FrameDetectionBoxes;
	return Result;
}
