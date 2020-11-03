// Dmitry Tabakerov is learning Unreal Engine 4

#include "Components/AudioComponent.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;
    FindAudioComponent();
    
	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component but no pressure plate"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TotalMassOfActor() > OpenMass   ) {
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else {
		if (GetWorld()->GetTimeSeconds() > DoorLastOpened + DoorCloseDelay)
		CloseDoor(DeltaTime);
	}
	
}


void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator Rotator = GetOwner()->GetActorRotation();

	Rotator.Yaw = FMath::FInterpTo(Rotator.Yaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	
    if (Rotator.Yaw == OpenAngle) { return; }
    
    GetOwner()->SetActorRelativeRotation(Rotator);
    
    if (!AudioComponent) {
        UE_LOG(LogTemp, Error, TEXT("%s missing AudioComponent!"), *GetOwner()->GetName());
        return;
    }

    if (!OpenDoorSound) {
        AudioComponent->Play();
        OpenDoorSound = true;
        CloseDoorSound = false;
    }
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator Rotator = GetOwner()->GetActorRotation();
    
    if (Rotator.Yaw == InitialYaw) { return; }
    
	Rotator.Yaw = FMath::FInterpTo(Rotator.Yaw, InitialYaw, DeltaTime, DoorCloseSpeed);
	GetOwner()->SetActorRelativeRotation(Rotator);
    
    if (!AudioComponent) {
        UE_LOG(LogTemp, Error, TEXT("%s missing AudioComponent!"), *GetOwner()->GetName());
        return;
    }

    if (!CloseDoorSound) {
        AudioComponent->Play();
        CloseDoorSound = true;
        OpenDoorSound = false;
    }
}

float UOpenDoor::TotalMassOfActor() const
{
    float TotalMass = 0.f;
    
    
    if (!PressurePlate) { return TotalMass; }

    //Find things within the volume
    TArray<AActor*> OverlapingActors;

    PressurePlate->GetOverlappingActors(
                                        OUT OverlapingActors);

    for (AActor* Actor : OverlapingActors) {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
        
    return TotalMass;
}

void UOpenDoor::FindAudioComponent()
{
    AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
    if (!AudioComponent) {
        UE_LOG(LogTemp, Error, TEXT("%s missing AudioComponent!"), *GetOwner()->GetName());
    }
}
