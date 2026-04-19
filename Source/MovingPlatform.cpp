#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	DistanceMoved = GetDistanceMoved();
	
	if (DistanceMoved >= MoveDistance)
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;

		SetActorLocation(NewStartLocation);
		StartLocation = NewStartLocation;
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
	
}

float AMovingPlatform::GetDistanceMoved()
{
	return 	FVector::Dist(StartLocation, GetActorLocation());
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator RotationToAdd = RotationVelocity * DeltaTime;
	AddActorLocalRotation(RotationToAdd);
}

