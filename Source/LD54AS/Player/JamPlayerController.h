// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LD54AS/Actors/HeroPawn.h"
#include "JamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LD54AS_API AJamPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY()
	UUserWidget *PauseMenuInstance;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> EndGameClass;

	UPROPERTY()
	UUserWidget *EndGameInstance;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget *HUDInstance;

	virtual void BeginPlay() override;
	AHeroPawn* GetHero();
	UFUNCTION(BlueprintCallable)
	void MoveRight(FKey key);
	UFUNCTION(BlueprintCallable)
	void MoveLeft(FKey key);
	UFUNCTION(BlueprintCallable)
	void MoveUp(FKey key);
	UFUNCTION(BlueprintCallable)
	void MoveDown(FKey key);
	UFUNCTION(BlueprintCallable)
	void Restart(FKey key);
	UFUNCTION(BlueprintCallable)
	void Skip(FKey key);
	UFUNCTION(BlueprintCallable)
	void Previous(FKey key);
	UFUNCTION(BlueprintCallable)
	void ShowEndGame();
	UFUNCTION(BlueprintCallable)
	void HideEndGame();

	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu(FKey key);
	
};
