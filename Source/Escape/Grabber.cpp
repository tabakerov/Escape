// Dmitry Tabakerov is learning Unreal Engine 4


#include "DrawDebugHelpers.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    FindPhysicsHandle();
    FindInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (PhysicsHandle->GrabbedComponent) {
        PhysicsHandle->SetTargetLocation(GetGrabbingPoint());
    }
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabbing"));
    
    FHitResult HitResult = GetFirstPhysicsBodyInReach();
    if (HitResult.GetActor()) {
        UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
        PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetGrabbingPoint());
    }
}

void UGrabber::Release() {
    UE_LOG(LogTemp, Warning, TEXT("Releasing!"));
    PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent) {
        InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("%s did not get InputComponent"), *GetOwner()->GetName());
    }
}

void UGrabber::FindPhysicsHandle()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle) {
        // NOOP
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("%s did not get PhysicsHandle"), *GetOwner()->GetName());
    }
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
    FHitResult Hit;
    FCollisionQueryParams TraceQueryParams(FName(TEXT("")), false, GetOwner());
    FVector PlayerViewpointLocation;
    FRotator PlayerViewpointRotation;
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewpointLocation,
        OUT PlayerViewpointRotation);
    
    GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewpointLocation,
        GetGrabbingPoint(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceQueryParams
    );

    return Hit;
}

FVector UGrabber::GetGrabbingPoint() const
{
    FVector PlayerViewpointLocation;
    FRotator PlayerViewpointRotation;
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewpointLocation,
        OUT PlayerViewpointRotation);

    return PlayerViewpointLocation + PlayerViewpointRotation.Vector()*Reach;
}
