// Copyright(C)2023 Valerio Santinelli


#include "StretchComponent.h"

#include "GroundCheckComponent.h"


// Sets default values for this component's properties
UStretchComponent2::UStretchComponent2()
{
	SqueezeTimeline = CreateDefaultSubobject<UTimelineComponent>("SqueezeTimeline");
	StretchTimeline = CreateDefaultSubobject<UTimelineComponent>("StretchTimeline");
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStretchComponent2::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh = Cast<UMeshComponent>(GetOwner()->GetComponentByClass(UMeshComponent::StaticClass()));
	InitialScale = BaseMesh->GetRelativeScale3D();

	GroundCheck = Cast<UGroundCheckComponent2>(GetOwner()->GetComponentByClass(UGroundCheckComponent2::StaticClass()));

	ProgressSqueezeTimeline.BindUFunction(this, FName("ProgressSqueeze"));
	ProgressStretchTimeline.BindUFunction(this, FName("ProgressStretch"));


	if (SqueezeCurve == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("You must set a curve for squeezing"));
	}
	else
	{
		SqueezeTimeline->AddInterpVector(SqueezeCurve, ProgressSqueezeTimeline);
	}

	if (SqueezeCurve == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("You must set a curve for stretching"));
	}
	else
	{
		StretchTimeline->AddInterpVector(StretchCurve, ProgressStretchTimeline);
	}
	
}


// Called every frame
void UStretchComponent2::TickComponent(float DeltaTime, ELevelTick TickType,
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

void UStretchComponent2::Stretch()
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

void UStretchComponent2::Squeeze()
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

void UStretchComponent2::ProgressSqueeze(FVector Value)
{
	// Log(f"Squeeze progress {Value}");
	FVector Scale = InitialScale;
	Scale *= Value;
	BaseMesh->SetRelativeScale3D(Scale);
}

void UStretchComponent2::ProgressStretch(FVector Value)
{
	// Log(f"Stretch progress {Value}");
	FVector Scale = InitialScale;
	Scale *= Value;
	BaseMesh->SetRelativeScale3D(Scale);
}
