// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameGrid.h"
#include "GameFramework/Actor.h"
#include "GridGen.generated.h"

class ATargetActor2;
class ACratePawn2;
class AHeroPawn2;
class AWallPawn2;

UCLASS()
class LD54AS_API AGridGen2 : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSubclassOf<AWallPawn2> Wall;

	UPROPERTY()
	TSubclassOf<AHeroPawn2> Hero;

	UPROPERTY()
	TSubclassOf<ACratePawn2> Crate;
    
	UPROPERTY()
	TSubclassOf<ATargetActor2> Target;

	UPROPERTY()
	TArray<FString> AllGrids;

	// Sets default values for this actor's properties
	AGridGen2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	FString GridFromNumber(int GridNumber);

	UFUNCTION(BlueprintCallable)
	int NumLevels();

	UFUNCTION(BlueprintCallable)
	void GenerateLevel(FGrid2 G);
};
