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
class LD54AS_API UJamSaveSystem2 : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UJamSaveGame2> CurrentSaveGame;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
public:
	UFUNCTION(BlueprintCallable)
	void ReadSaveGame();
	UFUNCTION(BlueprintCallable)
	void WriteSaveGame();
};
