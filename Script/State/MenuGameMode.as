class AMenuGameModeBase : AGameModeBase
{
    default PlayerStateClass = AJamPlayerState::StaticClass();
	default PlayerControllerClass = AJamPlayerController::StaticClass();

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        UJamSaveSystem SaveSystem = UJamSaveSystem::Get();
        SaveSystem.ReadSaveGame();
        UpdateAudioVolumes();
    }

    UFUNCTION(BlueprintCallable)
    int GetCurrentLevel() 
    {
        UJamSaveSystem SaveSystem = UJamSaveSystem::Get();
        return SaveSystem.CurrentSaveGame.CurrentLevel; 
    }

    UFUNCTION(BlueprintCallable)
    void ResetCurrentLevelAndSave()
    {
        UJamSaveSystem SaveSystem = UJamSaveSystem::Get();
        SaveSystem.CurrentSaveGame.CurrentLevel = 1;
        SaveSystem.WriteSaveGame(); 
    }

    void UpdateAudioVolumes()
	{
        UJamSaveSystem SaveSystem = UJamSaveSystem::Get();
        TArray<AAmbientSound> AmbientSounds;
        GetAllActorsOfClass(AAmbientSound::StaticClass(), AmbientSounds);
        for (int i = 0 ; i < AmbientSounds.Num() ; i++ ) {
            AAmbientSound AS = AmbientSounds[i];
            AS.AudioComponent.SetVolumeMultiplier(SaveSystem.CurrentSaveGame.MusicVolumeMultiplier);
        }
	}
}