// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

// Tick
	// Super
	// AimTowardsCrosshair();
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	// UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Tick ticking .."));
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; } // e.g. if not possessing (for example in editor runtime)
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter - now (at init time) is just 0,0,0
	if (GetSightRayHitLocation(HitLocation)) { // has "side-effect", is going to line trace
		// if it hits the landscape

		AimingComponent->AimAt(HitLocation);
		// Tell controlled tank to aim at this point

	}

}

// Get world location through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	// Find the crossahir position in pixel coordinates

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); // We pass variables to be filled! :-) now they are ..

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that look direction, and see what we hit (up to a max range)
		//UE_LOG(LogTemp, Warning, TEXT("CameraWorldDirection: %s"), *LookDirection.ToString());
		GetLookVectorHitLocation(LookDirection, HitLocation);

	}

	return true;

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {

	FVector CameraWorldLocation; // Variable to be discarded
	// "De-Project" the screen position of the crosshair to a world direction
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);

}



