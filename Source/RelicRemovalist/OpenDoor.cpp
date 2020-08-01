// Copyright Jonathan Moallem 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"

#define OUT


UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    InitialYaw = GetOwner()->GetActorRotation().Yaw;
    OpenYaw += InitialYaw;
    Player = GetWorld()->GetFirstPlayerController()->GetPawn();

    SetupAudio();

    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("TriggerVolume not assigned to %s actor!"), *GetOwner()->GetName())
    }

    if (!Player)
    {
        UE_LOG(LogTemp, Error, TEXT("Player not found!"))
    }


    if (Audio)
    {
        Audio->Play();
    }
}


void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Player && PressurePlate->IsOverlappingActor(Player))
    {
        bTriggered = true;
    }

    if (!bTriggered)
    {
        AdjustDoor(DeltaTime, OpenYaw, OpenSpeed);
        return;
    }

    if (!PressurePlate) { return; }
	TArray<AActor*> OverlappingActors;
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);

    float TotalMass = 0.f;
    for (int32 i = 0; i < OverlappingActors.Num(); i++)
    {
        if (OverlappingActors[i] != Player)
        {
            TotalMass += OverlappingActors[i]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        }
    }

    if (TotalMass >= MassRequired)
    {
        AdjustDoor(DeltaTime, OpenYaw, OpenSpeed);
        TimeSinceLastAdjust = GetWorld()->GetTimeSeconds();
        PlaySoundIfChange(true);
    }
    else if (GetWorld()->GetTimeSeconds() > TimeSinceLastAdjust + TimeToClose)
    {
        AdjustDoor(DeltaTime, InitialYaw, CloseSpeed);
        PlaySoundIfChange(false);
    }
}


void UOpenDoor::PlaySoundIfChange(bool IsOpening)
{
    if (!Audio) { return; }

    if (bLastOpened != IsOpening)
    {
        Audio->Play();
        bLastOpened = IsOpening;
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

void UOpenDoor::SetupAudio()
{
    Audio = GetOwner()->FindComponentByClass<UAudioComponent>();
    if (!Audio)
    {
        UE_LOG(LogTemp, Error, TEXT("No audio component attached to %s!"), *GetOwner()->GetName())
    }
}