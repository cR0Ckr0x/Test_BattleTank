// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	if (!BarrelToSet) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Barrel set! %s"), *(BarrelToSet->GetName()));

	Barrel = BarrelToSet;

}
void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Turret set! %s"), *(TurretToSet->GetName()));

	Turret = TurretToSet;

}

// Public Methods
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	/*auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);
	*/
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // this parameter must be present to prevent bug (Non aim solution found)
	);
	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); // We first get Barrel rotation (through forward vector)
	auto AimAsRotator = AimDirection.Rotation(); // then we get rotation of AimDirection
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}