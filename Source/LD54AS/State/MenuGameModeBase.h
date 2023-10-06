// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LD54AS_API AMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMenuGameModeBase(const FObjectInitializer& ObjectIn...);

	UFUNCTION(BlueprintCallable)
	int GetCurrentLevel();
	UFUNCTION(BlueprintCallable)
	void ResetCurrentLevelAndSave();
	UFUNCTION(BlueprintCallable)
	void UpdateAudioVolumes();
private:
	virtual void BeginPlay() override;


};