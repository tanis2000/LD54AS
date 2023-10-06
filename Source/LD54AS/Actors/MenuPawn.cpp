// Copyright(C)2023 Valerio Santinelli


#include "MenuPawn.h"


// Sets default values
AMenuPawn2::AMenuPawn2()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMenuPawn2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMenuPawn2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMenuPawn2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

