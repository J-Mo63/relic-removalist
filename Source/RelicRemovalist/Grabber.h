// Copyright Jonathan Moallem 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RELICREMOVALIST_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrabber();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
    void Release();

private:

    UPROPERTY(EditAnywhere)
    int32 GrabReach = 100;

    UPhysicsHandleComponent* PhysicsHandle = nullptr;

    UInputComponent* InputComponent = nullptr;
};
