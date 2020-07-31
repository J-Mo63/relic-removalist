// Copyright Jonathan Moallem 2020


#include "DrawDebugHelpers.h"
#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"

#define OUT


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Setup component fields
    SetupPhysicsHandle();
    BindInput();

}


void UGrabber::SetupPhysicsHandle()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (!PhysicsHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("No physics handle attached to %s!"), *GetOwner()->GetName())
    }
}


void UGrabber::BindInput()
{
    UInputComponent* InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
    {
        FVector PlayerVPLocation;
        FVector PlayerReachLocation;
        GetPlayerLocationReach(OUT PlayerVPLocation, OUT PlayerReachLocation);
	    PhysicsHandle->SetTargetLocation(PlayerReachLocation);
    }
}


void UGrabber::Grab()
{
    FVector PlayerVPLocation;
    FVector PlayerReachLocation;
    GetPlayerLocationReach(OUT PlayerVPLocation, OUT PlayerReachLocation);

    FCollisionQueryParams QueryParams(NAME_None,false, GetOwner());

    FHitResult HitResult;
    if (PhysicsHandle && GetWorld()->LineTraceSingleByObjectType(OUT HitResult, PlayerVPLocation,
            PlayerReachLocation, FCollisionObjectQueryParams(ECC_PhysicsBody), QueryParams))
    {
        PhysicsHandle->GrabComponentAtLocation(HitResult.GetComponent(), NAME_None, PlayerReachLocation);
    }
}


void UGrabber::Release()
{
    if (!PhysicsHandle) { return; }
    PhysicsHandle->ReleaseComponent();
}


void UGrabber::GetPlayerLocationReach(FVector &PlayerVPLocation, FVector &PlayerReachLocation) const
{
    FRotator PlayerVPRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerVPLocation, OUT PlayerVPRotation);
    PlayerReachLocation = PlayerVPLocation + PlayerVPRotation.Vector() * GrabReach;
}