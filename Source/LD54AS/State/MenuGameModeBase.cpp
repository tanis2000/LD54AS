// Copyright(C)2023 Valerio Santinelli


#include "MenuGameModeBase.h"

#include "JamPlayerState.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LD54AS/Player/JamPlayerController.h"
#include "LD54AS/Systems/JamSaveSystem.h"
#include "Sound/AmbientSound.h"

AMenuGameModeBase::AMenuGameModeBase(const FObjectInitializer& ObjectIn, ...): Super(ObjectIn)
{
	PlayerStateClass = AJamPlayerState::StaticClass();
	PlayerControllerClass = AJamPlayerController::StaticClass();
}

void AMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UJamSaveSystem *SaveSystem = GetWorld()->GetSubsystem<UJamSaveSystem>();
	SaveSystem->ReadSaveGame();
	UpdateAudioVolumes();
}


int AMenuGameModeBase::GetCurrentLevel() 
{
	UJamSaveSystem *SaveSystem = GetWorld()->GetSubsystem<UJamSaveSystem>();
	return SaveSystem->CurrentSaveGame->CurrentLevel; 
}


void AMenuGameModeBase::ResetCurrentLevelAndSave()
{
	UJamSaveSystem *SaveSystem = GetWorld()->GetSubsystem<UJamSaveSystem>();
	SaveSystem->CurrentSaveGame->CurrentLevel = 1;
	SaveSystem->WriteSaveGame(); 
}

void AMenuGameModeBase::UpdateAudioVolumes()
{
	UJamSaveSystem *SaveSystem = GetWorld()->GetSubsystem<UJamSaveSystem>();
	TArray<AActor *> AmbientSounds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), AmbientSounds);
	for (int i = 0 ; i < AmbientSounds.Num() ; i++ ) {
		AAmbientSound *AS = Cast<AAmbientSound>(AmbientSounds[i]);
		AS->GetAudioComponent()->SetVolumeMultiplier(SaveSystem->CurrentSaveGame->MusicVolumeMultiplier);
	}
}
