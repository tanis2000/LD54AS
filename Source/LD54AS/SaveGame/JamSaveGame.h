// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "JamSaveGame.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LD54AS_API UJamSaveGame2 : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float MusicVolumeMultiplier = 1;
    
	UPROPERTY(BlueprintReadWrite)
	float SoundEffectsVolumeMultiplier = 1;

	UPROPERTY(BlueprintReadWrite)
	int CurrentLevel = 1;

	UJamSaveGame2();
};
