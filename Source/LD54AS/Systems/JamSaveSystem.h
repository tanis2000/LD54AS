// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "LD54AS/SaveGame/JamSaveGame.h"
#include "Subsystems/WorldSubsystem.h"
#include "JamSaveSystem.generated.h"

/**
 * 
 */
UCLASS()
class LD54AS_API UJamSaveSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UJamSaveGame> CurrentSaveGame;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
public:
	UFUNCTION(BlueprintCallable)
	void ReadSaveGame();
	UFUNCTION(BlueprintCallable)
	void WriteSaveGame();
};
