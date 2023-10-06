// Copyright(C)2023 Valerio Santinelli


#include "CratePawn.h"

#include "HeroPawn.h"
#include "TargetActor.h"
#include "Components/AudioComponent.h"
#include "LD54AS/Libraries/SoundStatics.h"


// Sets default values
ACratePawn::ACratePawn()
{
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = Collider;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);

	Audio = CreateDefaultSubobject<UAudioComponent>("Audio");

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACratePawn::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation = GetActorLocation();

	BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &ACratePawn::OnBeginOverlap);
	BaseMesh->OnComponentEndOverlap.AddDynamic(this, &ACratePawn::OnEndOverlap);
}

// Called every frame
void ACratePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	if (IsOnTarget())
	{
		BaseMesh->SetMaterial(0, TriggeredMaterial);
	}
	else
	{
		BaseMesh->SetMaterial(0, BaseMaterial);
	}
}

// Called to bind functionality to input
void ACratePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ACratePawn::CanMove(const FVector &Direction)
{
	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation != TargetLocation)
	{
		return false;
	}

	FVector Start = GetActorLocation();
	FVector End = Start + Direction * 80;
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		return false;
	}
	return true;
}

void ACratePawn::Move(float DeltaSeconds)
{
	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation == TargetLocation)
	{
		return;
	}

	if ((CurrentLocation - TargetLocation).GetAbs().Size() < 10)
	{
		SetActorLocation(TargetLocation);
		return;
	}

	FVector Direction = (TargetLocation - CurrentLocation);
	Direction.Normalize();
	FVector NewLocation = CurrentLocation + (Direction * MovementSpeed * DeltaSeconds);

	FHitResult Hit;
	// SetActorLocation(NewLocation, true, Hit, true); 
	SetActorLocation(NewLocation);
}

void ACratePawn::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Display, TEXT("Crate OnBeginOverlap %s"), *OtherActor->GetClass()->GetName());

		AHeroPawn* Hero = Cast<AHeroPawn>(OtherActor);
		if (Hero != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT(">> %s"), SweepResult.ImpactNormal);
			if (CanMove(SweepResult.ImpactNormal))
			{
				TargetLocation = GetActorLocation() + SweepResult.ImpactNormal * 100;
			}
		}

		ATargetActor* Target = Cast<ATargetActor>(OtherActor);
		if (Target != nullptr)
		{
			USoundStatics::PlayRandomSFX(GetWorld(), Audio, DoneSound);
		}
	}
}

void ACratePawn::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	// Log(f"OnEndOverlap {OtherActor.Tags.Num()}");
}

bool ACratePawn::IsOnTarget()
{
	FVector Start = GetActorLocation();
	FVector End = Start + FVector::DownVector * 100;
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		ATargetActor* Target = Cast<ATargetActor>(Hit.GetActor());
		if (Target != nullptr)
		{
			return true;
		}
		return false;
	}
	return false;
}
