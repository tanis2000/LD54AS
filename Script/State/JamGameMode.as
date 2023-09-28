class AJamGameMode: AGameModeBase
{
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MusicVolumeMultiplier = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SoundEffectsVolumeMultiplier = 1;

    UPROPERTY()
    UJamSaveGame CurrentSaveGame;
    default CurrentSaveGame = UJamSaveGame();

    default PlayerStateClass = AJamPlayerState::StaticClass();
    default PlayerControllerClass = AJamPlayerController::StaticClass();

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        ReadSaveGame();
    }

    void WriteSaveGame()
    {
        CurrentSaveGame = UJamSaveGame();
        CurrentSaveGame.MusicVolumeMultiplier = MusicVolumeMultiplier;
        CurrentSaveGame.SoundEffectsVolumeMultiplier = SoundEffectsVolumeMultiplier;
        Gameplay::SaveGameToSlot(CurrentSaveGame, "Slot1", 0);
        Print("Save game created");
    }

    void ReadSaveGame()
    {
        if (Gameplay::DoesSaveGameExist("Slot1", 0)) {
            CurrentSaveGame = Cast<UJamSaveGame>(Gameplay::LoadGameFromSlot("Slot1", 0));
            MusicVolumeMultiplier = CurrentSaveGame.MusicVolumeMultiplier;
            SoundEffectsVolumeMultiplier = CurrentSaveGame.SoundEffectsVolumeMultiplier;
            Print("Save game loaded");
        } else {
            Print("No save game found");
        }
    }
}