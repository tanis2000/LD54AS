// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "JamSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LD54AS_API UJamSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float MusicVolumeMultiplier = 1;
    
	UPROPERTY()
	float SoundEffectsVolumeMultiplier = 1;

	UPROPERTY(BlueprintReadWrite)
	int CurrentLevel = 1;

	UJamSaveGame();
};
