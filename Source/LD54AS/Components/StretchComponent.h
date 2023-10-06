// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "StretchComponent.generated.h"


class UGroundCheckComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LD54AS_API UStretchComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector *SqueezeCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector *StretchCurve;

	UPROPERTY()
	UTimelineComponent *SqueezeTimeline = nullptr;

	UPROPERTY()
	UTimelineComponent *StretchTimeline = nullptr;

	FOnTimelineVector ProgressSqueezeTimeline;
	FOnTimelineVector ProgressStretchTimeline;
	FVector InitialScale;
	UMeshComponent *BaseMesh = nullptr;
	UGroundCheckComponent *GroundCheck = nullptr;

	// Sets default values for this component's properties
	UStretchComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void Stretch();

	UFUNCTION(BlueprintCallable)
	void Squeeze();
	
	UFUNCTION(BlueprintCallable)
	void ProgressSqueeze(FVector Value);

	UFUNCTION(BlueprintCallable)
	void ProgressStretch(FVector Value);
};
