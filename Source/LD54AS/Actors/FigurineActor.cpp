// Copyright(C)2023 Valerio Santinelli


#include "FigurineActor.h"


// Sets default values
AFigurineActor::AFigurineActor()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

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

