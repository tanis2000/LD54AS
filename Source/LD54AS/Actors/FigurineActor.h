// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FigurineActor.generated.h"

class URotatingMovementComponent;

UCLASS()
class LD54AS_API AFigurineActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URotatingMovementComponent *RotatingMovement;


	// Sets default values for this actor's properties
	AFigurineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
