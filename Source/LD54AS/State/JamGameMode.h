// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LD54AS/Generators/Grid/GridGen.h"
#include "JamGameMode.generated.h"

class UJamSaveGame;

UENUM()
enum class EGameState {
	Initializing,
	Transitioning,
	Playing,
	End,
};

/**
 * 
 */
UCLASS()
class LD54AS_API AJamGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicVolumeMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundEffectsVolumeMultiplier = 1;

	UPROPERTY()
	UJamSaveGame *CurrentSaveGame;

	UPROPERTY()
	EGameState CurrentGameState;

	UPROPERTY()
	TArray<AActor *> Targets;
	UPROPERTY()
	TArray<AActor *> Heroes;
	UPROPERTY()
	TArray<AActor *> Walls;
	UPROPERTY()
	TArray<AActor *> Crates;
	
	AJamGameMode(const FObjectInitializer& ObjectIn...);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void WriteSaveGame();

	UFUNCTION(BlueprintCallable)
	void ReadSaveGame();
	void UpdateAudioVolumes();
	void CollectTargets();
	void CheckWinCondition();
	void NextLevel();
	AGridGen* GetGridGen();
	void GenerateLevel(int LevelNumber);
	void SubmitScore(int Score);
	void CleanUp();

	UFUNCTION(BlueprintCallable)
	void RestartLevel();

	UFUNCTION(BlueprintCallable)
	void SkipLevel();

	UFUNCTION(BlueprintCallable)
	void PreviousLevel();
	void CheckEndGame();
	void ShowEndGame();
};
