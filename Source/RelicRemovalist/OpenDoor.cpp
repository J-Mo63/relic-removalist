// Copyright Jonathan Moallem 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    InitialYaw = GetOwner()->GetActorRotation().Yaw;
    TargetYaw += InitialYaw;
    Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}


void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (TriggerVolume->IsOverlappingActor(Player))
    {
        OpenDoor(DeltaTime);
    }
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
    FRotator Rotation = GetOwner()->GetActorRotation();
    float Difference = abs(Rotation.Yaw - TargetYaw);
    if (Difference > 0.0f || Difference == 360.f)
    {
        Rotation.Yaw = (Difference < 0.1f) ? TargetYaw : FMath::FInterpConstantTo(Rotation.Yaw, TargetYaw, DeltaTime, 30);
        GetOwner()->SetActorRotation(Rotation);
    }
}