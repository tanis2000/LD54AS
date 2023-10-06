// Copyright(C)2023 Valerio Santinelli


#include "HeroPawn.h"

#include "CratePawn.h"
#include "WallPawn.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LD54AS/Components/StretchComponent.h"
#include "LD54AS/Libraries/SoundStatics.h"


// Sets default values
AHeroPawn2::AHeroPawn2()
{
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = Collider;

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(Collider);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");

	Stretch = CreateDefaultSubobject<UStretchComponent2>("Stretch");

	Audio = CreateDefaultSubobject<UAudioComponent>("Audio");

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHeroPawn2::BeginPlay()
{
	Super::BeginPlay();
	TargetLocation = GetActorLocation();

	BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &AHeroPawn2::OnBeginOverlap);
	BaseMesh->OnComponentEndOverlap.AddDynamic(this, &AHeroPawn2::OnEndOverlap);

	GetMovementComponent()->UpdatedComponent = RootComponent;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACratePawn2::StaticClass(), Crates);
}

// Called every frame
void AHeroPawn2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
	PlaySounds();
}

// Called to bind functionality to input
void AHeroPawn2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AHeroPawn2::CanMove(FVector Direction)
{
	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation != TargetLocation)
	{
		return false;
	}

	FVector Start = GetActorLocation();
	FVector End = Start + Direction * 80;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		ACratePawn2* Crate = Cast<ACratePawn2>(Hit.GetActor());
		if (Crate != nullptr)
		{
			if (Crate->CanMove(Direction))
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

void AHeroPawn2::Move(float DeltaSeconds)
{
	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation == TargetLocation)
	{
		bMoving = false;
		bPushing = false;
		return;
	}

	bMoving = true;
	bPushing = true;

	if ((CurrentLocation - TargetLocation).GetAbs().Size() < 10)
	{
		SetActorLocation(TargetLocation);
		// Stretch.Squeeze();
		return;
	}

	FVector Direction = (TargetLocation - CurrentLocation);
	Direction.Normalize();
	FVector TotalDistance = TargetLocation - StartingLocation;
	FVector ActualDistance = TargetLocation - CurrentLocation;
	float Diff = ActualDistance.Size() / TotalDistance.Size();
	FVector InterpOffset = MovementInterpolationCurve->GetVectorValue(Diff);
	FVector NewLocation = CurrentLocation + (Direction * MovementSpeed * DeltaSeconds) * InterpOffset;

	FHitResult Hit;
	SetActorLocation(NewLocation, true, &Hit, ETeleportType::TeleportPhysics);
	// SetActorLocation(NewLocation); 
}

void AHeroPawn2::PerformMove(FVector Direction)
{
	if (!bMoving && !bPushing && PathIsBlocked(Direction))
	{
		USoundStatics::PlayRandomSFX(GetWorld(), Audio, BlockedSound);
	}
	if (CanMove(Direction))
	{
		if (WillTryToPushCrate(Direction))
		{
			USoundStatics::PlayRandomSFX(GetWorld(), Audio, PushSound);
		}
		else
		{
			USoundStatics::PlayRandomSFX(GetWorld(), Audio, MoveSound);
		}
		StartingLocation = GetActorLocation();
		FaceDirection(Direction);
		// Stretch.Stretch();
		TargetLocation = GetActorLocation() + Direction * 100;
	}
}

void AHeroPawn2::MoveRight()
{
	FVector Direction = FVector::RightVector;
	PerformMove(Direction);
}

void AHeroPawn2::MoveLeft()
{
	FVector Direction = FVector::LeftVector;
	PerformMove(Direction);
}

void AHeroPawn2::MoveUp()
{
	FVector Direction = FVector::ForwardVector;
	PerformMove(Direction);
}

void AHeroPawn2::MoveDown()
{
	FVector Direction = FVector::BackwardVector;
	PerformMove(Direction);
}

void AHeroPawn2::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("OnBeginOverlap %d"), OtherActor->Tags.Num());
}

void AHeroPawn2::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("OnEndOverlap %d"), OtherActor->Tags.Num());
}

void AHeroPawn2::FaceDirection(FVector Direction)
{
	FVector NewForward = Direction;
	NewForward.Normalize();
	FRotator Rotator = NewForward.Rotation();
	SetActorRotation(Rotator);
}

void AHeroPawn2::PlaySounds()
{
	if (!bMoving && !bPushing && !Audio->IsPlaying() && FMath::RandRange(0.0, 1.0) < 0.003)
	{
		USoundStatics::PlayRandomSFX(GetWorld(), Audio, IdleSound);
	}
}

bool AHeroPawn2::WillTryToPushCrate(FVector Direction)
{
	FVector Start = GetActorLocation();
	FVector End = Start + Direction * 80;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		ACratePawn2* Crate = Cast<ACratePawn2>(Hit.GetActor());
		if (Crate != nullptr)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool AHeroPawn2::PathIsBlocked(FVector Direction)
{
	FVector Start = GetActorLocation();
	FVector End = Start + Direction * 80;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		ACratePawn2* Crate = Cast<ACratePawn2>(Hit.GetActor());
		if (Crate != nullptr)
		{
			if (!Crate->CanMove(Direction))
			{
				return true;
			}
		}
	}

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		AWallPawn2* Wall = Cast<AWallPawn2>(Hit.GetActor());
		if (Wall != nullptr)
		{
			return true;
		}
	}
	return false;
}
