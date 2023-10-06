// Copyright(C)2023 Valerio Santinelli


#include "GroundCheckComponent.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UGroundCheckComponent2::UGroundCheckComponent2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGroundCheckComponent2::BeginPlay()
{
	Super::BeginPlay();

	GroundChecker = Cast<UArrowComponent>(GetOwner()->GetComponentByClass(UArrowComponent::StaticClass()));
}


// Called every frame
void UGroundCheckComponent2::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bWasOnGround = bIsOnGround;
	bIsOnGround = IsOnGround();
}

bool UGroundCheckComponent2::IsOnGround()
{
	// Log(f"Owner {Owner.GetName()}");
	FHitResult Hit;
	FVector Start = GroundChecker->GetComponentLocation();
	FVector End = Start;
	End.Z -= GroundProbeLength;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	// Log(f"Start {Start}");

	UKismetSystemLibrary::DrawDebugLine(GetWorld(), Start, End, FLinearColor::Green, 1, 5);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		// Log(f"Trace hit {Hit.GetComponent().GetFullName()}");
		return true;
	}

	return false;
}

bool UGroundCheckComponent2::GetIsOnGround()
{
	return bIsOnGround;
}

bool UGroundCheckComponent2::GetWasOnGround()
{
	return bWasOnGround;
}
