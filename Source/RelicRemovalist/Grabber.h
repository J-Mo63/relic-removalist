// Copyright Jonathan Moallem 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RELICREMOVALIST_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:

	UGrabber();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

private:

    void SetupPhysicsHandle();
    void BindInput();

    void Grab();
    void Release();

    UPROPERTY(EditAnywhere)
    int32 GrabReach = 100;

    UPhysicsHandleComponent* PhysicsHandle = nullptr;
};
