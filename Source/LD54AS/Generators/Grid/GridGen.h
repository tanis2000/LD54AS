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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWallPawn> Wall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AHeroPawn> Hero;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACratePawn> Crate;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATargetActor> Target;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> AllGrids;

	// Sets default values for this actor's properties
	AGridGen();

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
	void GenerateLevel(FGrid G);
};
