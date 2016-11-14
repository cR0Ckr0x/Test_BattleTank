// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	// No need to call Super as we're replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	//					  (Magnitude of A * Mag of B * cos of angle between A and B)
	// Dot Product: A*B = ||A||*||B||*cos(Theta)
	// (Represents the Parallellness of 2 vector. If 2 vectors are parallel (theta=0), then it's A*B and it's at maximum - if vectors are perpendicolar (theta=90), then cos(90)=0 and dot product is 0)
	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveforward(ForwardThrow);
	UE_LOG(LogTemp, Warning, TEXT("%s: move velocity: %s"), *(GetOwner()->GetName()), *(AIForwardIntention.ToString()));
}


void UTankMovementComponent::IntendMoveforward(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	// TODO prevent double-speed due to dual control use
}

