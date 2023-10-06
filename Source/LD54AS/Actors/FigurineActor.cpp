// Copyright(C)2023 Valerio Santinelli


#include "FigurineActor.h"


// Sets default values
AFigurineActor2::AFigurineActor2()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFigurineActor2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFigurineActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

