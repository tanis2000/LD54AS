class UJamSaveGame : USaveGame
{
    UPROPERTY()
    float MusicVolumeMultiplier;
    
    UPROPERTY()
    float SoundEffectsVolumeMultiplier;

    UPROPERTY(BlueprintReadWrite)
    int CurrentLevel;
}