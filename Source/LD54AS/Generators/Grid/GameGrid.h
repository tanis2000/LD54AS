// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameGrid.generated.h"

USTRUCT(Blueprintable)
struct FGrid2 {
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
class LD54AS_API UGameGrid2 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FGrid2 ParseLevel(FString Str);

	UFUNCTION(BlueprintCallable)
	static int NumLevels();
};
