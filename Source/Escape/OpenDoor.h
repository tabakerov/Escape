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

private:
	float CurrentYaw;
	float InitialYaw;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	UPROPERTY(EditAnywhere);
	float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere);
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere);
	AActor* ActorThatOpens;
};
