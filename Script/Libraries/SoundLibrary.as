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
}