// Copyright(C)2023 Valerio Santinelli


#include "TestActor.h"

#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LD54AS/Components/GroundCheckComponent.h"
#include "LD54AS/Components/StretchComponent.h"
#include "LD54AS/Libraries/SoundStatics.h"
#include "LD54AS/State/JamGameMode.h"


// Sets default values
ATestActor::ATestActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = SceneRoot;

	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetupAttachment(SceneRoot);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);

	GroundCheckAttachment = CreateDefaultSubobject<UArrowComponent>("GroundCheckAttachment");
	GroundCheckAttachment->SetupAttachment(BaseMesh);

	GroundCheck = CreateDefaultSubobject<UGroundCheckComponent>("GroundCheck");
	GroundCheck->SetupAttachment(BaseMesh);

	Stretch = CreateDefaultSubobject<UStretchComponent>("Stretch");

	InputComponent = CreateDefaultSubobject<UInputComponent>("InputComponent");

	Audio = CreateDefaultSubobject<UAudioComponent>("Audio");

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentHit.AddDynamic(this, &ATestActor::OnHit);
	BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &ATestActor::OnBeginOverlap);
	BaseMesh->OnComponentEndOverlap.AddDynamic(this, &ATestActor::OnEndOverlap);

	GameMode = Cast<AJamGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATestActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATestActor::Jump()
{
	UE_LOG(LogTemp, Display, TEXT("Trying to jump"));
	Collider->AddImpulse(FVector::UpVector * 500, NAME_None, true);
	Stretch->Stretch();
	USoundStatics::PlaySFX(GetWorld(), Audio, JumpSound);
	// Audio.SetSound(JumpSound);
	// Audio.SetVolumeMultiplier(GameMode.SoundEffectsVolumeMultiplier);
	// Audio.Play();
}

void ATestActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                       FVector NormalImpulse, const FHitResult& Hit)
{
	//Log(f"Hit {OtherActor.Tags.Num()} {Hit.bBlockingHit}");
	//Stretch.Squeeze();
}

void ATestActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	// Log(f"OnBeginOverlap {OtherActor.Tags.Num()}");
	Stretch->Squeeze();
}

void ATestActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	// Log(f"OnEndOverlap {OtherActor.Tags.Num()}");
}
