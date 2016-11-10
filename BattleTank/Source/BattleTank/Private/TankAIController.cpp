// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {

		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}

	// UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Tick ticking .."));
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Not possessing any tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI possessing tank: %s"), *(ControlledTank->GetName()));

		auto PlayerTank = GetPlayerTank();
		if (!PlayerTank) {
			UE_LOG(LogTemp, Warning, TEXT("%s could not find any Player Controller."), *(ControlledTank->GetName()));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("%s could find Player Controller: %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()));
		}
	}
}


ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}