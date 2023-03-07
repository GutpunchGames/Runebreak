#include "GameOrchestrator/LocalGameOrchestrator.h"
#include "GameOrchestrator/RBPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include <math.h>

#define FRAME_RATE 60
#define ONE_FRAME (1.0f / FRAME_RATE)

// Sets default values
ALocalGameOrchestrator::ALocalGameOrchestrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALocalGameOrchestrator::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay"))

	// Initialize the game state
	Simulation.Init();

	OnSessionStarted();
}

// Called every frame
void ALocalGameOrchestrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    ElapsedTime += DeltaTime;

    int32 IdleMs = (int32)(ONE_FRAME - (int32)(ElapsedTime * 1000));
    while (ElapsedTime >= ONE_FRAME) {
        TickGameState();
        ElapsedTime -= ONE_FRAME;
    }
}

void ALocalGameOrchestrator::OnSessionStarted_Implementation() { 
}

void ALocalGameOrchestrator::TickGameState()
{
    GetLocalInputs();
    RunFrame();
}

void ALocalGameOrchestrator::RunFrame()
{
    GGPOErrorCode result = GGPO_OK;
    Simulation.Update(Inputs, 0);
	UE_LOG(LogTemp, Warning, TEXT("synchronize_input success"))
}

void ALocalGameOrchestrator::GetLocalInputs() {
    const UObject* world = (UObject*)GetWorld();
    ARBPlayerController* Controller = Cast<ARBPlayerController>(UGameplayStatics::GetPlayerController(world, 0));

    if (Controller)
    {
         Inputs[0] = Controller->GetPlayerInput();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get input"))
    }
}

FTransform ALocalGameOrchestrator::GetPlayerTransform(int32 PlayerIndex) {
    const Player player = Simulation._players[PlayerIndex];
    FVector Position = FVector(0, (float)player.position.x, (float)player.position.y);
    FQuat Rotation = FRotator(0, 0, 0).Quaternion();
    FTransform Result = FTransform(Rotation, Position);
    return Result;
}
