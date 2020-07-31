// Copyright Jonathan Moallem 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RELICREMOVALIST_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:

	UOpenDoor();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void AdjustDoor(float DeltaTime, float TargetAngle, float Speed);

protected:

    virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;

    UPROPERTY(EditAnywhere)
    AActor* TriggerObject;

    UPROPERTY(EditAnywhere)
    float OpenSpeed = 1.f;

    UPROPERTY(EditAnywhere)
    float CloseSpeed = 1.f;

    UPROPERTY(EditAnywhere)
    float TimeToClose = 1.f;

    UPROPERTY(EditAnywhere)
    float TargetYaw = 0.f;

    float InitialYaw = 0.f;

    float TimeSinceLastAdjust = 0.f;
};
