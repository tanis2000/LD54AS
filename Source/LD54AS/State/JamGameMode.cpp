// Copyright(C)2023 Valerio Santinelli


#include "JamGameMode.h"

#include "JamGameInstance.h"
#include "JamPlayerState.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LD54AS/Actors/CratePawn.h"
#include "LD54AS/Actors/HeroPawn.h"
#include "LD54AS/Actors/TargetActor.h"
#include "LD54AS/Actors/WallPawn.h"
#include "LD54AS/Generators/Grid/GridGen.h"
#include "LD54AS/Leaderboard/LeaderboardActor.h"
#include "LD54AS/Player/JamPlayerController.h"
#include "LD54AS/SaveGame/JamSaveGame.h"
#include "Sound/AmbientSound.h"

AJamGameMode2::AJamGameMode2(const FObjectInitializer& ObjectIn, ...): Super(ObjectIn)
{
	CurrentSaveGame = Cast<UJamSaveGame2>(UGameplayStatics::CreateSaveGameObject(UJamSaveGame2::StaticClass()));
	PlayerStateClass = AJamPlayerState2::StaticClass();
	PlayerControllerClass = AJamPlayerController2::StaticClass();
}

void AJamGameMode2::BeginPlay()
{
	CurrentGameState = EGameState2::Initializing;
	UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetGameInstance());
	ReadSaveGame();
	UpdateAudioVolumes();
	GetGridGen()->Initialize();
	GenerateLevel(GI->CurrentLevel);
	CollectTargets();
}

void AJamGameMode2::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentGameState)
	{
	case EGameState2::Playing:
		CheckWinCondition();
		break;
	case EGameState2::Transitioning:
		CheckEndGame();
		NextLevel();
		break;
	case EGameState2::End:
		ShowEndGame();
		break;
	default: ;
	}
}

void AJamGameMode2::WriteSaveGame()
{
	UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetGameInstance());
	CurrentSaveGame = Cast<UJamSaveGame2>(UGameplayStatics::CreateSaveGameObject(UJamSaveGame2::StaticClass()));
	CurrentSaveGame->MusicVolumeMultiplier = MusicVolumeMultiplier;
	CurrentSaveGame->SoundEffectsVolumeMultiplier = SoundEffectsVolumeMultiplier;
	CurrentSaveGame->CurrentLevel = GI->CurrentLevel;
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, "Slot1", 0);
	UE_LOG(LogTemp, Display, TEXT("Save game created"));
}

void AJamGameMode2::ReadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("Slot1", 0))
	{
		UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetGameInstance());
		CurrentSaveGame = Cast<UJamSaveGame2>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
		MusicVolumeMultiplier = CurrentSaveGame->MusicVolumeMultiplier;
		SoundEffectsVolumeMultiplier = CurrentSaveGame->SoundEffectsVolumeMultiplier;
		GI->CurrentLevel = CurrentSaveGame->CurrentLevel;
		UE_LOG(LogTemp, Display, TEXT("Save game loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No save game found"));
	}
}

void AJamGameMode2::UpdateAudioVolumes()
{
	TArray<AActor*> AmbientSounds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), AmbientSounds);
	for (int i = 0; i < AmbientSounds.Num(); i++)
	{
		AAmbientSound* AS = Cast<AAmbientSound>(AmbientSounds[i]);
		AS->GetAudioComponent()->SetVolumeMultiplier(MusicVolumeMultiplier);
	}
}

void AJamGameMode2::CollectTargets()
{
	Targets.Reset();
	Heroes.Reset();
	Walls.Reset();
	Crates.Reset();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetActor2::StaticClass(), Targets);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHeroPawn2::StaticClass(), Heroes);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWallPawn2::StaticClass(), Walls);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACratePawn2::StaticClass(), Crates);
}

void AJamGameMode2::CheckWinCondition()
{
	if (CurrentGameState != EGameState2::Playing)
	{
		return;
	}

	for (int i = 0; i < Targets.Num(); i++)
	{
		ATargetActor2* Target = Cast<ATargetActor2>(Targets[i]);
		if (!Target->HasCrate())
		{
			return;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Win"));

	CurrentGameState = EGameState2::Transitioning;
	UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetWorld()->GetGameInstance());
	SubmitScore(GI->CurrentLevel);
	GI->CurrentLevel++;
	WriteSaveGame();
}

void AJamGameMode2::NextLevel()
{
	UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetWorld()->GetGameInstance());
	CleanUp();
	GenerateLevel(GI->CurrentLevel);
	CollectTargets();
}

AGridGen2* AJamGameMode2::GetGridGen()
{
	TArray<AActor*> GridGens;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridGen2::StaticClass(), GridGens);
	AGridGen2* GridGen = Cast<AGridGen2>(GridGens[0]);
	return GridGen;
}

void AJamGameMode2::GenerateLevel(int LevelNumber)
{
	AGridGen2* GridGen = GetGridGen();
	if (LevelNumber > GridGen->NumLevels())
	{
		return;
	}
	FGrid2 G = UGameGrid2::ParseLevel(GridGen->GridFromNumber(LevelNumber));
	GridGen->GenerateLevel(G);
	CurrentGameState = EGameState2::Playing;
}

void AJamGameMode2::SubmitScore(int Score)
{
	UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetWorld()->GetGameInstance());
	TArray<AActor*> Leaderboards;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALeaderboardActor::StaticClass(), Leaderboards);
	ALeaderboardActor* Leaderboard = Cast<ALeaderboardActor>(Leaderboards[0]);
	Leaderboard->SubmitScore(GI->PlayerDisplayName.ToString(), Score);
}

void AJamGameMode2::CleanUp()
{
	for (int i = 0; i < Targets.Num(); i++)
	{
		AActor* Actor = Targets[i];
		Actor->Destroy();
	}
	for (int i = 0; i < Heroes.Num(); i++)
	{
		AActor* Actor = Heroes[i];
		Actor->Destroy();
	}
	for (int i = 0; i < Walls.Num(); i++)
	{
		AActor* Actor = Walls[i];
		Actor->Destroy();
	}
	for (int i = 0; i < Crates.Num(); i++)
	{
		AActor* Actor = Crates[i];
		Actor->Destroy();
	}
}

void AJamGameMode2::RestartLevel()
{
	CurrentGameState = EGameState2::Transitioning;
	NextLevel();
}

void AJamGameMode2::SkipLevel()
{
	CurrentGameState = EGameState2::Transitioning;
	UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetWorld()->GetGameInstance());
	GI->CurrentLevel++;
}

void AJamGameMode2::PreviousLevel()
{
	CurrentGameState = EGameState2::Transitioning;
	UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetWorld()->GetGameInstance());
	if (GI->CurrentLevel > 1)
	{
		GI->CurrentLevel--;
	}
}

void AJamGameMode2::CheckEndGame()
{
	UJamGameInstance2* GI = Cast<UJamGameInstance2>(GetWorld()->GetGameInstance());
	AGridGen2* GridGen = GetGridGen();
	if (GI->CurrentLevel > GridGen->NumLevels())
	{
		CurrentGameState = EGameState2::End;
	}
}

void AJamGameMode2::ShowEndGame()
{
	AJamPlayerController2* PC = Cast<AJamPlayerController2>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->ShowEndGame();
}
