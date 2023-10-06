// Copyright(C)2023 Valerio Santinelli


#include "CratePawn.h"

#include "HeroPawn.h"
#include "TargetActor.h"
#include "Components/AudioComponent.h"
#include "LD54AS/Libraries/SoundStatics.h"


// Sets default values
ACratePawn2::ACratePawn2()
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
void ACratePawn2::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation = GetActorLocation();

	BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &ACratePawn2::OnBeginOverlap);
	BaseMesh->OnComponentEndOverlap.AddDynamic(this, &ACratePawn2::OnEndOverlap);
}

// Called every frame
void ACratePawn2::Tick(float DeltaTime)
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
void ACratePawn2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ACratePawn2::CanMove(const FVector &Direction)
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

void ACratePawn2::Move(float DeltaSeconds)
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

void ACratePawn2::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Display, TEXT("Crate OnBeginOverlap %s"), *OtherActor->GetClass()->GetName());

		AHeroPawn2* Hero = Cast<AHeroPawn2>(OtherActor);
		if (Hero != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT(">> %s"), SweepResult.ImpactNormal);
			if (CanMove(SweepResult.ImpactNormal))
			{
				TargetLocation = GetActorLocation() + SweepResult.ImpactNormal * 100;
			}
		}

		ATargetActor2* Target = Cast<ATargetActor2>(OtherActor);
		if (Target != nullptr)
		{
			USoundStatics::PlayRandomSFX(GetWorld(), Audio, DoneSound);
		}
	}
}

void ACratePawn2::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	// Log(f"OnEndOverlap {OtherActor.Tags.Num()}");
}

bool ACratePawn2::IsOnTarget()
{
	FVector Start = GetActorLocation();
	FVector End = Start + FVector::DownVector * 100;
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		ATargetActor2* Target = Cast<ATargetActor2>(Hit.GetActor());
		if (Target != nullptr)
		{
			return true;
		}
		return false;
	}
	return false;
}
