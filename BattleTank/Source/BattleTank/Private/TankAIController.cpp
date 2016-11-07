// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = getControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Not possessing any tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI possessing tank: %s"), *(ControlledTank->GetName()));

		auto PlayerTank = getPlayerTank();
		if (!PlayerTank) {
			UE_LOG(LogTemp, Warning, TEXT("%s could not find any Player Controller."), *(ControlledTank->GetName()));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("%s could find Player Controller: %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()));
		}
	}
}

ATank* ATankAIController::getControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::getPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}