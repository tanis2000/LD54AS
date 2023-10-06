// Copyright(C)2023 Valerio Santinelli


#include "SoundStatics.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LD54AS/State/JamGameMode.h"

void USoundStatics::PlaySFX(UWorld* World, UAudioComponent *Audio, USoundBase *Sound)
{
	AJamGameMode2 *GameMode = Cast<AJamGameMode2>(UGameplayStatics::GetGameMode(World));
	Audio->SetSound(Sound);
	Audio->SetVolumeMultiplier(GameMode->SoundEffectsVolumeMultiplier);
	Audio->Play();
}

void USoundStatics::PlayRandomSFX(UWorld* World, UAudioComponent *Audio, TArray<USoundBase *> Sound)
{
	int idx = FMath::RandRange(0, Sound.Num()-1);
	PlaySFX(World, Audio, Sound[idx]);
}
