// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* getControlledTank() const; // const = it's not gonna change any variable of this class

	virtual void BeginPlay() override; // please make sure there's this exact function up the inheritance tree (parent class)
	// in this case I can ovveride BeginPlay() because it was declared virtual (virtual void BeginPlay();)
	// So it can be overridden by any ancestor in the future
	// nell'override è irrilevante se si specifica virtual. Qualsiasi ancestor futuro potrà fare override dalla funzione parent virtual senza doverlo rispecificare
	
	
};
