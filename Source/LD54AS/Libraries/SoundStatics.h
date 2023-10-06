// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoundStatics.generated.h"

/**
 * 
 */
UCLASS()
class LD54AS_API USoundStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void PlaySFX(UWorld* World, UAudioComponent* Audio, USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	static void PlayRandomSFX(UWorld* World, UAudioComponent *Audio, TArray<USoundBase *> Sound);
};
