// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank) {
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // todo check radius is in cm

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire(); // TODO limit firing rate
	}

}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}