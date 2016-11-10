// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(FRotator AimRotator) {
	// Ottenendo una AimDirection (FRotator)
	// Calcolo la direzione di rotazione più vicina all'AimDirection
	// 
	// Ruoto in DeltaTime verso quella direzione
	bool goLeft = true;
	//UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *(RelativeRotation.ToString()));
	//UE_LOG(LogTemp, Warning, TEXT("Current rotation: %d | %d | %d | %d"), RelativeRotation.Yaw, AimRotator.Yaw, (AimRotator.Yaw - RelativeRotation.Yaw), (RelativeRotation.Yaw - AimRotator.Yaw));
	/*if (
		(AimRotator.Yaw - RelativeRotation.Yaw)
		<
		(RelativeRotation.Yaw - AimRotator.Yaw)
		) {
		goLeft = false;
	}*/


	//auto RelativeSpeed = FMath::Clamp<float>(AimRotator.Yaw, -1, +1);
	//auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // with DeltaTimeSeconds I make the elevation frame-rate independent
	//auto RawNewElevation = RelativeRotation.Yaw + RotationChange;
	//UE_LOG(LogTemp, Warning, TEXT("Turret rotation: %d"), RawNewElevation);
	//SetRelativeRotation(FRotator(0, 0, RawNewElevation));

	SetRelativeRotation(AimRotator);

	/*if (Rela)
		AimRotator.Yaw
		*/

		/*
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // with DeltaTimeSeconds I make the elevation frame-rate independent
	auto RawNewElevation = RelativeRotation.Yaw + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, Rotation));
	*/

}