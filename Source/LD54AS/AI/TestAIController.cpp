// Copyright(C)2023 Valerio Santinelli


#include "TestAIController.h"

#include "LD54AS/Actors/TestActor.h"


// Sets default values
ATestAIController2::ATestAIController2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestAIController2::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Hi from the AI"));
	GetWorld()->GetTimerManager().SetTimer(ThinkTimerHandle, this, &ATestAIController2::Think, 3.0f, true);
}

// Called every frame
void ATestAIController2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestAIController2::Think()
{
	UE_LOG(LogTemp, Display, TEXT("AI is thinking"));
	ATestActor2 *MyPawn = Cast<ATestActor2>(GetPawn());
	MyPawn->Jump();
}
