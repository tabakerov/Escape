// Dmitry Tabakerov is learning Unreal Engine 4


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
	TargetYaw += InitialYaw;

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component but no pressure plate"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && ActorThatOpens && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
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
	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), Rotator.Yaw);

	Rotator.Yaw = FMath::FInterpTo(Rotator.Yaw, TargetYaw, DeltaTime, 2.f);
	GetOwner()->SetActorRelativeRotation(Rotator);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator Rotator = GetOwner()->GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), Rotator.Yaw);

	Rotator.Yaw = FMath::FInterpTo(Rotator.Yaw, InitialYaw, DeltaTime, 2.f);
	GetOwner()->SetActorRelativeRotation(Rotator);
}