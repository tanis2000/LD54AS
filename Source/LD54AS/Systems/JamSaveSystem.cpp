// Copyright(C)2023 Valerio Santinelli


#include "JamSaveSystem.h"

#include "Kismet/GameplayStatics.h"
#include "LD54AS/SaveGame/JamSaveGame.h"

void UJamSaveSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSaveGame = Cast<UJamSaveGame>(UGameplayStatics::CreateSaveGameObject(UJamSaveGame::StaticClass()));
}

void UJamSaveSystem::ReadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("Slot1", 0))
	{
		CurrentSaveGame = Cast<UJamSaveGame>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
		UE_LOG(LogTemp, Display, TEXT("SS: Save game loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("SS: No save game found"));
	}
}

void UJamSaveSystem::WriteSaveGame()
{
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, "Slot1", 0);
	UE_LOG(LogTemp, Display, TEXT("SS: Save game created"));
}