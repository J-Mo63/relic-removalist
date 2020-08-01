// Copyright Jonathan Moallem 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RELICREMOVALIST_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:

	UOpenDoor();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

    virtual void BeginPlay() override;

private:

    void AdjustDoor(float DeltaTime, float TargetAngle, float Speed);

    void PlaySoundIfChange(bool IsOpening);

    void SetupAudio();

    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
    float OpenSpeed = 1.f;

    UPROPERTY(EditAnywhere)
    float CloseSpeed = 1.f;

    UPROPERTY(EditAnywhere)
    float TimeToClose = 1.f;

    UPROPERTY(EditAnywhere)
    float OpenYaw = 0.f;

    UPROPERTY(EditAnywhere)
    float MassRequired = 50.f;

    UPROPERTY()
    UAudioComponent* Audio = nullptr;

    AActor* Player = nullptr;

    float InitialYaw = 0.f;

    float TimeSinceLastAdjust = 0.f;

    bool bLastOpened = true;

    bool bTriggered = false;
};
