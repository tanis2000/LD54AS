// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameGrid.h"
#include "GameFramework/Actor.h"
#include "GridGen.generated.h"

class ATargetActor;
class ACratePawn;
class AHeroPawn;
class AWallPawn;

UCLASS()
class LD54AS_API AGridGen : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSubclassOf<AWallPawn> Wall;

	UPROPERTY()
	TSubclassOf<AHeroPawn> Hero;

	UPROPERTY()
	TSubclassOf<ACratePawn> Crate;
    
	UPROPERTY()
	TSubclassOf<ATargetActor> Target;

	UPROPERTY()
	TArray<FString> AllGrids;

	// Sets default values for this actor's properties
	AGridGen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Initialize();
	FString GridFromNumber(int GridNumber);
	int NumLevels();
	void GenerateLevel(FGrid G);
};
