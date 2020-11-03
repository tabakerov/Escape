// Dmitry Tabakerov is learning Unreal Engine 4

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
private:
	float Reach = 100.f;

	UPROPERTY(EditAnywhere);
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY(EditAnywhere);
	UInputComponent* InputComponent = nullptr;

    void Grab();
    void Release();
    void FindPhysicsHandle();
    void FindInputComponent();
    FHitResult GetFirstPhysicsBodyInReach() const;
    FVector GetGrabbingPoint() const;
};
