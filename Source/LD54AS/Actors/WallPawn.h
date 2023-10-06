// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WallPawn.generated.h"

class UBoxComponent;

UCLASS()
class LD54AS_API AWallPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent *Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *BaseMesh;

	// Sets default values for this pawn's properties
	AWallPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
