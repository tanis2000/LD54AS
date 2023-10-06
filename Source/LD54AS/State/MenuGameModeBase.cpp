// Copyright(C)2023 Valerio Santinelli


#include "MenuGameModeBase.h"

#include "JamPlayerState.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LD54AS/Player/JamPlayerController.h"
#include "LD54AS/Systems/JamSaveSystem.h"
#include "Sound/AmbientSound.h"

AMenuGameModeBase2::AMenuGameModeBase2(const FObjectInitializer& ObjectIn, ...): Super(ObjectIn)
{
	PlayerStateClass = AJamPlayerState2::StaticClass();
	PlayerControllerClass = AJamPlayerController2::StaticClass();
}

void AMenuGameModeBase2::BeginPlay()
{
	Super::BeginPlay();
	UJamSaveSystem2 *SaveSystem = GetWorld()->GetSubsystem<UJamSaveSystem2>();
	SaveSystem->ReadSaveGame();
	UpdateAudioVolumes();
}


int AMenuGameModeBase2::GetCurrentLevel() 
{
	UJamSaveSystem2 *SaveSystem = GetWorld()->GetSubsystem<UJamSaveSystem2>();
	return SaveSystem->CurrentSaveGame->CurrentLevel; 
}


void AMenuGameModeBase2::ResetCurrentLevelAndSave()
{
	UJamSaveSystem2 *SaveSystem = GetWorld()->GetSubsystem<UJamSaveSystem2>();
	SaveSystem->CurrentSaveGame->CurrentLevel = 1;
	SaveSystem->WriteSaveGame(); 
}

void AMenuGameModeBase2::UpdateAudioVolumes()
{
	UJamSaveSystem2 *SaveSystem = GetWorld()->GetSubsystem<UJamSaveSystem2>();
	TArray<AActor *> AmbientSounds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), AmbientSounds);
	for (int i = 0 ; i < AmbientSounds.Num() ; i++ ) {
		AAmbientSound *AS = Cast<AAmbientSound>(AmbientSounds[i]);
		if (AS) {
			UAudioComponent* AC = AS->GetAudioComponent();
			if (AC) {
				AC->SetVolumeMultiplier(SaveSystem->CurrentSaveGame->MusicVolumeMultiplier);
			}
		}
	}
}
