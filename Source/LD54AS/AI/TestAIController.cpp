// Copyright(C)2023 Valerio Santinelli


#include "TestAIController.h"

#include "LD54AS/Actors/TestActor.h"


// Sets default values
ATestAIController::ATestAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Hi from the AI"));
	GetWorld()->GetTimerManager().SetTimer(ThinkTimerHandle, this, &ATestAIController::Think, 3.0f, true);
}

// Called every frame
void ATestAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestAIController::Think()
{
	UE_LOG(LogTemp, Display, TEXT("AI is thinking"));
	ATestActor *Pawn = Cast<ATestActor>(GetPawn());
	Pawn->Jump();
}
