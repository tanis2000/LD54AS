// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "CratePawn.generated.h"

UCLASS()
class LD54AS_API ACratePawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent *Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance *BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance *TriggeredMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent *Audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundBase *> DoneSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 500;

	FVector TargetLocation;
	
	// Sets default values for this pawn's properties
	ACratePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool CanMove(FVector Direction);
	void Move(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int OtherBodyIndex);
	bool IsOnTarget();
};
