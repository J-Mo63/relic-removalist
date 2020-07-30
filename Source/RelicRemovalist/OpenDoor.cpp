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
    TriggerObject = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("TriggerVolume not assigned to %s actor!"), *GetOwner()->GetName());
    }
}


void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate && PressurePlate->IsOverlappingActor(TriggerObject))
    {
        AdjustDoor(DeltaTime, TargetYaw, OpenSpeed);
        TimeSinceLastAdjust = GetWorld()->GetTimeSeconds();
    }
    else if (GetWorld()->GetTimeSeconds() > TimeSinceLastAdjust + TimeToClose)
    {
        AdjustDoor(DeltaTime, InitialYaw, CloseSpeed);
    }
}


void UOpenDoor::AdjustDoor(float DeltaTime, float TargetAngle, float Speed)
{
    FRotator Rotation = GetOwner()->GetActorRotation();
    float Difference = abs(Rotation.Yaw - TargetAngle);
    if (Difference > 0.0f || Difference == 360.f)
    {
        Rotation.Yaw = (Difference < 0.1f) ? TargetAngle : FMath::FInterpConstantTo(Rotation.Yaw, TargetAngle, DeltaTime, 30 * Speed);
        GetOwner()->SetActorRotation(Rotation);
    }
}