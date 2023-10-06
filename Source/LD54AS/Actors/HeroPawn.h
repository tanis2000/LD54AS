// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "HeroPawn.generated.h"

class UBoxComponent;
class UStretchComponent;

UCLASS()
class LD54AS_API AHeroPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent *Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent *Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFloatingPawnMovement *MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStretchComponent *Stretch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent *Audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector *MovementInterpolationCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundBase *> IdleSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundBase *> MoveSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundBase *> PushSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundBase *> BlockedSound;

	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0, ClampMax=1))
	float MovementSfxChance = 0.1f;
	
	UPROPERTY()
	TArray<AActor *> Crates;

	FVector StartingLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPushing;
	
	// Sets default values for this pawn's properties
	AHeroPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool CanMove(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void Move(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	void PerformMove(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void MoveRight();

	UFUNCTION(BlueprintCallable)
	void MoveLeft();

	UFUNCTION(BlueprintCallable)
	void MoveUp();

	UFUNCTION(BlueprintCallable)
	void MoveDown();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void FaceDirection(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void PlaySounds();

	UFUNCTION(BlueprintCallable)
	bool WillTryToPushCrate(FVector Direction);

	UFUNCTION(BlueprintCallable)
	bool PathIsBlocked(FVector Direction);
};
