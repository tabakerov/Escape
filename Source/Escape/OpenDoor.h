// Dmitry Tabakerov is learning Unreal Engine 4

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h" // this one should be the last #include in the list


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
    
    // Calculate mass of things within the volume
    float TotalMassOfActor() const;

private:
    bool OpenDoorSound = false;
    bool CloseDoorSound = true;
	float CurrentYaw;
	float InitialYaw;
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere);
	float OpenAngle = 90.f;
    
    UPROPERTY(EditAnywhere);
    float OpenMass = 40.f;

	UPROPERTY(EditAnywhere);
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere);
	float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere);
	float DoorOpenSpeed = 2.f;

	UPROPERTY(EditAnywhere);
	float DoorCloseSpeed = 2.f;
    
    UPROPERTY();
    UAudioComponent* AudioComponent = nullptr;
    void FindAudioComponent();
};
