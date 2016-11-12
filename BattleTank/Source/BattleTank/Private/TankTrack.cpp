// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // GetOwner gives me the top component (Tank_BP) - GetRootComponent gives me Tank (The Tank component, a Static Mesh Component)
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



