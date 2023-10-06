// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestActor.generated.h"

class AJamGameMode;
class UStretchComponent;
class UGroundCheckComponent;
class UArrowComponent;
class UBoxComponent;

UCLASS()
class LD54AS_API ATestActor : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent *SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent *Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent *GroundCheckAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGroundCheckComponent *GroundCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStretchComponent *Stretch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent *Audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave *JumpSound;

	UPROPERTY()
	AJamGameMode *GameMode;
	
	// Sets default values for this pawn's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& Hit);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int OtherBodyIndex);
};
