// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JamPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LD54AS_API AJamPlayerPawn2 : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent *SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent *SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent *Camera;

	// Sets default values for this pawn's properties
	AJamPlayerPawn2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
