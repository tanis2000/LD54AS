// Copyright(C)2023 Valerio Santinelli


#include "WallPawn.h"

#include "Components/BoxComponent.h"


// Sets default values
AWallPawn::AWallPawn()
{
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = Collider;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWallPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
