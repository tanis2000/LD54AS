class AMenuGameModeBase : AGameModeBase
{
    default PlayerStateClass = AJamPlayerState::StaticClass();
	default PlayerControllerClass = AJamPlayerController::StaticClass();

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        UJamSaveSystem SaveSystem = UJamSaveSystem::Get();
        SaveSystem.ReadSaveGame();
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
}