class UJamSaveSystem: UScriptWorldSubsystem
{
    UPROPERTY()
	UJamSaveGame CurrentSaveGame;
	default CurrentSaveGame = UJamSaveGame();

    UFUNCTION(BlueprintOverride)
    void Initialize()
    {
        
    }

    UFUNCTION(BlueprintCallable)
    void ReadSaveGame()
	{
		if (Gameplay::DoesSaveGameExist("Slot1", 0))
		{
			CurrentSaveGame = Cast<UJamSaveGame>(Gameplay::LoadGameFromSlot("Slot1", 0));
			Log("SS: Save game loaded");
		}
		else
		{
			Log("SS: No save game found");
		}
	}

    void WriteSaveGame()
	{
		Gameplay::SaveGameToSlot(CurrentSaveGame, "Slot1", 0);
		Log("SS: Save game created");
	}

}