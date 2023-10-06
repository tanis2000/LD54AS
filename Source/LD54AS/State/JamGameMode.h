// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LD54AS/Generators/Grid/GridGen.h"
#include "JamGameMode.generated.h"

class UJamSaveGame2;

UENUM()
enum class EGameState2 {
	Initializing,
	Transitioning,
	Playing,
	End,
};

/**
 * 
 */
UCLASS()
class LD54AS_API AJamGameMode2 : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicVolumeMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundEffectsVolumeMultiplier = 1;

	UPROPERTY()
	UJamSaveGame2 *CurrentSaveGame;

	UPROPERTY()
	EGameState2 CurrentGameState;

	UPROPERTY()
	TArray<AActor *> Targets;
	UPROPERTY()
	TArray<AActor *> Heroes;
	UPROPERTY()
	TArray<AActor *> Walls;
	UPROPERTY()
	TArray<AActor *> Crates;
	
	AJamGameMode2(const FObjectInitializer& ObjectIn...);
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
	AGridGen2* GetGridGen();
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
