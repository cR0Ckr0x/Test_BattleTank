// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration - that allows us to reference the type UTankBarrel down in .h file without a chain of dependancy (to avoid #include manually)
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Aiming,
	Locked,
	Reloading
};


// Hold barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus CurrentFiringStatus = EFiringStatus::Aiming;

private:

	// Sets default values for this component's properties
	UTankAimingComponent();

	// preso da UActorComponent -> Go to definition -> cercare nel suo file sorgente 'tick'
	/**
	* Function called every frame on this ActorComponent. Override this function to implement custom logic to be executed every frame.
	* Only executes if the component is registered, and also PrimaryComponentTick.bCanEverTick must be set to true.
	*
	* @param DeltaTime - The time since the last tick.
	* @param TickType - The kind of tick this is, for example, are we paused, or 'simulating' in the editor
	* @param ThisTickFunction - Internal tick function struct that caused this to run
	*/
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	//UStaticMeshComponent* Barrel = nullptr;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;



	// TODO remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

};
