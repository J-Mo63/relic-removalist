// Copyright Jonathan Moallem 2020


#include "DrawDebugHelpers.h"
#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();
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

	// Get viewpoint
	// Perform raycast to distance
}

