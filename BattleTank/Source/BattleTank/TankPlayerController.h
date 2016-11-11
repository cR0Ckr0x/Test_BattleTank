// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankPlayerController);

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const; // const = it's not gonna change any variable of this class

	virtual void BeginPlay() override; // please make sure there's this exact function up the inheritance tree (parent class)
	// in this case I can ovveride BeginPlay() because it was declared virtual (virtual void BeginPlay();)
	// So it can be overridden by any ancestor in the future
	// nell'override è irrilevante se si specifica virtual. Qualsiasi ancestor futuro potrà fare override dalla funzione parent virtual senza doverlo rispecificare
	
	virtual void Tick( float DeltaTime ) override;

	// Start the tank moving the barrel so that a shot would it where
	// the crosshair intersects the world
	void AimTowardsCrosshair();


	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = .5;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = .33333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000; //

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHit) const;
	
};
