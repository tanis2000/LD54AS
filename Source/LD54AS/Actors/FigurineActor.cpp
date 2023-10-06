// Copyright(C)2023 Valerio Santinelli


#include "FigurineActor.h"

#include "GameFramework/RotatingMovementComponent.h"


// Sets default values
AFigurineActor::AFigurineActor()
{
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFigurineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFigurineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

