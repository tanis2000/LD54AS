// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameGrid.generated.h"

USTRUCT(Blueprintable)
struct FGrid {
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	int Width;

	UPROPERTY(BlueprintReadWrite)
	int Height;

	UPROPERTY(BlueprintReadWrite)
	TArray<int> Grid;
};

/**
 * 
 */
UCLASS(Blueprintable)
class LD54AS_API UGameGrid : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FGrid ParseLevel(FString Str);

	UFUNCTION(BlueprintCallable)
	static int NumLevels();
};
