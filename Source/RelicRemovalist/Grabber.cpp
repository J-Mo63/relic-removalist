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

	// Move the attached object
}


void UGrabber::Grab()
{
    FRotator PlayerVPRotation;
    FVector PlayerVPLocation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
            OUT PlayerVPLocation,
            OUT PlayerVPRotation
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
        UE_LOG(LogTemp, Warning, TEXT("GRABBED!"))
    }
}


void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("RELEASED!"))
}