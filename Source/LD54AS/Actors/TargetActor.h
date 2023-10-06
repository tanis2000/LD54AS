// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "TargetActor.generated.h"

UCLASS()
class LD54AS_API ATargetActor2 : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent *Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent *Particles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance *BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance *TriggeredMaterial;


	// Sets default values for this actor's properties
	ATargetActor2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool HasCrate();
};
