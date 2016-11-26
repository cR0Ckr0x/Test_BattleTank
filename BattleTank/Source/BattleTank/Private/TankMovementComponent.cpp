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

	// 1. Faccio avanzare back/forward AI Tank
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	// Vector DOT product
	//					  (Magnitude of A * Mag of B * cos of angle between A and B)
	// Dot Product: A*B = ||A||*||B||*cos(Theta)
	// (Represents the Parallellness of 2 vectors. If 2 vectors are parallel (theta=0), then it's A*B and it's at maximum - if vectors are perpendicolar (theta=90), then cos(90)=0 and dot product is 0)
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveforward(ForwardThrow);

	// 2. Ruoto AI Tank verso la direzione in cui deve andare
	// Vector CROSS product
	// A x B == ||A||*||B||*sen(theta)*n
	// Theta is the angle between A and B in the plane containing them (so between 0° and 180°
	// n is a unit vector prependicular to the plane
	// (Represents "PERPENDICULARITY" of 2 vectors. Maximum when vectors are perpendicular (sen(90°)=1), zero when they are parallel (sen(0°)=0 => Vector = A*B*0 = 0). Gives Always a Vector orthogonal to both. 
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}


void UTankMovementComponent::IntendMoveforward(float Throw) {
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

