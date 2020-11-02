// Dmitry Tabakerov is learning Unreal Engine 4


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator Rotator = GetOwner()->GetActorRotation();
	float CurrentYaw = Rotator.Yaw;
	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), Rotator.Yaw);

	Rotator.Yaw = FMath::FInterpTo(Rotator.Yaw, TargetYaw, DeltaTime, 2.f);
	GetOwner()->SetActorRelativeRotation(Rotator);
}

