// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GroundCheckComponent.generated.h"


class UArrowComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LD54AS_API UGroundCheckComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsOnGround = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bWasOnGround = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GroundProbeLength = 5.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent *GroundChecker = nullptr;

	// Sets default values for this component's properties
	UGroundCheckComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	bool IsOnGround();
	bool GetIsOnGround();
	bool GetWasOnGround();
};
