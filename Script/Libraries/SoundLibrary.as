namespace Sound
{
    UFUNCTION(BlueprintCallable)
    void PlaySFX(UAudioComponent Audio, USoundBase Sound)
    {
        AJamGameMode GameMode = Cast<AJamGameMode>(Gameplay::GetGameMode());
		Audio.SetSound(Sound);
		Audio.SetVolumeMultiplier(GameMode.SoundEffectsVolumeMultiplier);
		Audio.Play();
    }

    UFUNCTION(BlueprintCallable)
    void PlayRandomSFX(UAudioComponent Audio, TArray<USoundBase> Sound)
    {
        int idx = Math::RandRange(0, Sound.Num()-1);
        PlaySFX(Audio, Sound[idx]);
    }

}