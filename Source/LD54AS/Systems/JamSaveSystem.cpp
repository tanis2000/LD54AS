// Copyright(C)2023 Valerio Santinelli


#include "JamSaveSystem.h"

#include "Kismet/GameplayStatics.h"
#include "LD54AS/SaveGame/JamSaveGame.h"

void UJamSaveSystem2::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSaveGame = Cast<UJamSaveGame2>(UGameplayStatics::CreateSaveGameObject(UJamSaveGame2::StaticClass()));
}

void UJamSaveSystem2::ReadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("Slot1", 0))
	{
		CurrentSaveGame = Cast<UJamSaveGame2>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
		UE_LOG(LogTemp, Display, TEXT("SS: Save game loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("SS: No save game found"));
	}
}

void UJamSaveSystem2::WriteSaveGame()
{
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, "Slot1", 0);
	UE_LOG(LogTemp, Display, TEXT("SS: Save game created"));
}