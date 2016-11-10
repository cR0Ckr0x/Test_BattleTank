// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	void Rotate(FRotator AimRotator);

private:

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0;

	
	
};
