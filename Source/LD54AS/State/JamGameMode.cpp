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

AJamGameMode::AJamGameMode(const FObjectInitializer& ObjectIn, ...): Super(ObjectIn)
{
	CurrentSaveGame = Cast<UJamSaveGame>(UGameplayStatics::CreateSaveGameObject(UJamSaveGame::StaticClass()));
	PlayerStateClass = AJamPlayerState::StaticClass();
	PlayerControllerClass = AJamPlayerController::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

void AJamGameMode::BeginPlay()
{
	CurrentGameState = EGameState::Initializing;
	UJamGameInstance* GI = Cast<UJamGameInstance>(GetGameInstance());
	ReadSaveGame();
	UpdateAudioVolumes();
	AGridGen *GridGen = GetGridGen();
	if (GridGen)
	{
		GridGen->Initialize();
		GenerateLevel(GI->CurrentLevel);
		CollectTargets();
	}
}

void AJamGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentGameState)
	{
	case EGameState::Playing:
		CheckWinCondition();
		break;
	case EGameState::Transitioning:
		CheckEndGame();
		NextLevel();
		break;
	case EGameState::End:
		ShowEndGame();
		break;
	default: ;
	}
}

void AJamGameMode::WriteSaveGame()
{
	UJamGameInstance* GI = Cast<UJamGameInstance>(GetGameInstance());
	CurrentSaveGame = Cast<UJamSaveGame>(UGameplayStatics::CreateSaveGameObject(UJamSaveGame::StaticClass()));
	CurrentSaveGame->MusicVolumeMultiplier = MusicVolumeMultiplier;
	CurrentSaveGame->SoundEffectsVolumeMultiplier = SoundEffectsVolumeMultiplier;
	CurrentSaveGame->CurrentLevel = GI->CurrentLevel;
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, "Slot1", 0);
	UE_LOG(LogTemp, Display, TEXT("Save game created"));
}

void AJamGameMode::ReadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("Slot1", 0))
	{
		UJamGameInstance* GI = Cast<UJamGameInstance>(GetGameInstance());
		CurrentSaveGame = Cast<UJamSaveGame>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
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

void AJamGameMode::UpdateAudioVolumes()
{
	TArray<AActor*> AmbientSounds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), AmbientSounds);
	for (int i = 0; i < AmbientSounds.Num(); i++)
	{
		AAmbientSound* AS = Cast<AAmbientSound>(AmbientSounds[i]);
		AS->GetAudioComponent()->SetVolumeMultiplier(MusicVolumeMultiplier);
	}
}

void AJamGameMode::CollectTargets()
{
	Targets.Reset();
	Heroes.Reset();
	Walls.Reset();
	Crates.Reset();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetActor::StaticClass(), Targets);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHeroPawn::StaticClass(), Heroes);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWallPawn::StaticClass(), Walls);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACratePawn::StaticClass(), Crates);
}

void AJamGameMode::CheckWinCondition()
{
	if (CurrentGameState != EGameState::Playing)
	{
		return;
	}

	for (int i = 0; i < Targets.Num(); i++)
	{
		ATargetActor* Target = Cast<ATargetActor>(Targets[i]);
		if (!Target->HasCrate())
		{
			return;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Win"));

	CurrentGameState = EGameState::Transitioning;
	UJamGameInstance* GI = Cast<UJamGameInstance>(GetWorld()->GetGameInstance());
	SubmitScore(GI->CurrentLevel);
	GI->CurrentLevel++;
	WriteSaveGame();
}

void AJamGameMode::NextLevel()
{
	UJamGameInstance* GI = Cast<UJamGameInstance>(GetWorld()->GetGameInstance());
	CleanUp();
	GenerateLevel(GI->CurrentLevel);
	CollectTargets();
}

AGridGen* AJamGameMode::GetGridGen()
{
	AGridGen* GridGen = nullptr;
	TArray<AActor*> GridGens;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridGen::StaticClass(), GridGens);
	if (GridGens.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("you have to add a GridGen to the level"));
		return GridGen;
	}
	GridGen = Cast<AGridGen>(GridGens[0]);
	return GridGen;
}

void AJamGameMode::GenerateLevel(int LevelNumber)
{
	AGridGen* GridGen = GetGridGen();
	if (GridGen == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot generate the level. GridGen is missing in this level. You have to add one."));
		return;
	}
	
	if (LevelNumber > GridGen->NumLevels())
	{
		UE_LOG(LogTemp, Display, TEXT("Last level reached."));
		return;
	}
	FGrid G = UGameGrid::ParseLevel(GridGen->GridFromNumber(LevelNumber));
	GridGen->GenerateLevel(G);
	CurrentGameState = EGameState::Playing;
}

void AJamGameMode::SubmitScore(int Score)
{
	UJamGameInstance* GI = Cast<UJamGameInstance>(GetWorld()->GetGameInstance());
	TArray<AActor*> Leaderboards;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALeaderboardActor::StaticClass(), Leaderboards);
	ALeaderboardActor* Leaderboard = Cast<ALeaderboardActor>(Leaderboards[0]);
	Leaderboard->SubmitScore(GI->PlayerDisplayName.ToString(), Score);
}

void AJamGameMode::CleanUp()
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

void AJamGameMode::RestartLevel()
{
	CurrentGameState = EGameState::Transitioning;
	NextLevel();
}

void AJamGameMode::SkipLevel()
{
	CurrentGameState = EGameState::Transitioning;
	UJamGameInstance* GI = Cast<UJamGameInstance>(GetWorld()->GetGameInstance());
	GI->CurrentLevel++;
}

void AJamGameMode::PreviousLevel()
{
	CurrentGameState = EGameState::Transitioning;
	UJamGameInstance* GI = Cast<UJamGameInstance>(GetWorld()->GetGameInstance());
	if (GI->CurrentLevel > 1)
	{
		GI->CurrentLevel--;
	}
}

void AJamGameMode::CheckEndGame()
{
	UJamGameInstance* GI = Cast<UJamGameInstance>(GetWorld()->GetGameInstance());
	AGridGen* GridGen = GetGridGen();
	if (GI->CurrentLevel > GridGen->NumLevels())
	{
		CurrentGameState = EGameState::End;
	}
}

void AJamGameMode::ShowEndGame()
{
	AJamPlayerController* PC = Cast<AJamPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->ShowEndGame();
}
