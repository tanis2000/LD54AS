// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MenuPawn.generated.h"

UCLASS()
class LD54AS_API AMenuPawn2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMenuPawn2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
