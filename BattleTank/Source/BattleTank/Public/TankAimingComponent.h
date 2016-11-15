// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Aiming,
	Locked,
	Reloading
};

// Forward Declaration - that allows us to reference the type UTankBarrel down in .h file without a chain of dependancy (to avoid #include manually)
class UTankBarrel;
class UTankTurret;

// Hold barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus CurrentFiringStatus = EFiringStatus::Aiming;

private:

	// Sets default values for this component's properties
	UTankAimingComponent();

	//UStaticMeshComponent* Barrel = nullptr;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);	
};
