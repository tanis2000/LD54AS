// Copyright(C)2023 Valerio Santinelli


#include "StretchComponent.h"

#include "GroundCheckComponent.h"


// Sets default values for this component's properties
UStretchComponent::UStretchComponent()
{
	SqueezeTimeline = CreateDefaultSubobject<UTimelineComponent>("SqueezeTimeline");
	StretchTimeline = CreateDefaultSubobject<UTimelineComponent>("StretchTimeline");
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStretchComponent::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh = Cast<UMeshComponent>(GetOwner()->GetComponentByClass(UMeshComponent::StaticClass()));
	InitialScale = BaseMesh->GetRelativeScale3D();

	GroundCheck = Cast<UGroundCheckComponent>(GetOwner()->GetComponentByClass(UGroundCheckComponent::StaticClass()));

	ProgressSqueezeTimeline.BindUFunction(this, FName("ProgressSqueeze"));
	ProgressStretchTimeline.BindUFunction(this, FName("ProgressStretch"));


	if (SqueezeCurve == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: You must set a curve for squeezing"), *GetOwner()->GetName());
	}
	else
	{
		SqueezeTimeline->AddInterpVector(SqueezeCurve, ProgressSqueezeTimeline);
	}

	if (SqueezeCurve == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: You must set a curve for stretching"), *GetOwner()->GetName());
	}
	else
	{
		StretchTimeline->AddInterpVector(StretchCurve, ProgressStretchTimeline);
	}
	
}


// Called every frame
void UStretchComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (!GroundCheck.GetIsOnGround() && GroundCheck.GetWasOnGround())
	// {
	// 	Print("Started flying");
	// 	Stretch();
	// }
	// else if (GroundCheck.GetIsOnGround() && !GroundCheck.GetWasOnGround())
	// {
	// 	Print("Landed");
	// 	Squeeze();
	// }
}

void UStretchComponent::Stretch()
{
	UE_LOG(LogTemp, Display, TEXT("Stretch"));
	if (StretchTimeline->IsPlaying())
	{
		UE_LOG(LogTemp, Display, TEXT("Waiting for the stretch animation to finish"));
		return;
	}
	SqueezeTimeline->Stop();
	StretchTimeline->PlayFromStart();
}

void UStretchComponent::Squeeze()
{
	UE_LOG(LogTemp, Display, TEXT("Squeeze"));
	if (SqueezeTimeline->IsPlaying())
	{
		UE_LOG(LogTemp, Display, TEXT("Waiting for the squeeze animation to finish"));
		return;
	}
	StretchTimeline->Stop();
	SqueezeTimeline->PlayFromStart();
}

void UStretchComponent::ProgressSqueeze(FVector Value)
{
	// Log(f"Squeeze progress {Value}");
	FVector Scale = InitialScale;
	Scale *= Value;
	BaseMesh->SetRelativeScale3D(Scale);
}

void UStretchComponent::ProgressStretch(FVector Value)
{
	// Log(f"Stretch progress {Value}");
	FVector Scale = InitialScale;
	Scale *= Value;
	BaseMesh->SetRelativeScale3D(Scale);
}
