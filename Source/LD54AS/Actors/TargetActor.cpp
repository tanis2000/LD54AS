// Copyright(C)2023 Valerio Santinelli


#include "TargetActor.h"

#include "CratePawn.h"


// Sets default values
ATargetActor::ATargetActor()
{
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = Collider;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);

	Particles = CreateDefaultSubobject<UNiagaraComponent>("Particles");
	
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasCrate()) {
		BaseMesh->SetMaterial(0, TriggeredMaterial);
	} else {
		BaseMesh->SetMaterial(0, BaseMaterial);
	}
}

bool ATargetActor::HasCrate() {
	FVector Start = GetActorLocation();
	FVector End = Start + FVector::UpVector;
	TArray<AActor> Ignore;
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	if(GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params)) {
		ACratePawn *Crate = Cast<ACratePawn>(Hit.GetActor());
		if (Crate != nullptr) {
			return true;
		}
		return false;
	}
	return false;
}
