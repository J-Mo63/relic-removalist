// Copyright Jonathan Moallem 2020


#include "DrawDebugHelpers.h"
#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!PhysicsHandle)
    {
	    UE_LOG(LogTemp, Error, TEXT("No physics handle attached to %s!"), *GetOwner()->GetName());
    }

    if (!InputComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("No input component attached to %s!"), *GetOwner()->GetName());
    }
    else
    {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator PlayerVPRotation;
	FVector PlayerVPLocation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
	        OUT PlayerVPLocation,
	        OUT PlayerVPRotation
    );

    DrawDebugLine(
            GetWorld(),
            PlayerVPLocation,
            PlayerVPLocation + PlayerVPRotation.Vector() * GrabReach,
            FColor(0, 255, 0),
            false,
            0.f,
            0,
            5.f
    );

    FCollisionQueryParams QueryParams(FName(TEXT("")),false, GetOwner());
    FHitResult HitResult;
    bool bDidHit = GetWorld()->LineTraceSingleByObjectType(
            OUT HitResult,
            PlayerVPLocation,
            PlayerVPLocation + PlayerVPRotation.Vector() * GrabReach,
            FCollisionObjectQueryParams(ECC_PhysicsBody),
            QueryParams
    );

    if (bDidHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit a surface!"));
    }
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("GRABBED!"));
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("RELEASED!"));
}