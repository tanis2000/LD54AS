class AJamGameMode : AGameModeBase
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

	TArray<ATargetActor> Targets;

	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		ReadSaveGame();
		UpdateAudioVolumes();
		CollectTargets();
	}

	UFUNCTION(BlueprintOverride)
	void Tick(float DeltaSeconds)
	{
		CheckWinCondition();
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
		if (Gameplay::DoesSaveGameExist("Slot1", 0))
		{
			CurrentSaveGame = Cast<UJamSaveGame>(Gameplay::LoadGameFromSlot("Slot1", 0));
			MusicVolumeMultiplier = CurrentSaveGame.MusicVolumeMultiplier;
			SoundEffectsVolumeMultiplier = CurrentSaveGame.SoundEffectsVolumeMultiplier;
			Print("Save game loaded");
		}
		else
		{
			Print("No save game found");
		}
	}

	void UpdateAudioVolumes()
	{
        TArray<AAmbientSound> AmbientSounds;
        GetAllActorsOfClass(AAmbientSound::StaticClass(), AmbientSounds);
        for (int i = 0 ; i < AmbientSounds.Num() ; i++ ) {
            AAmbientSound AS = AmbientSounds[i];
            AS.AudioComponent.SetVolumeMultiplier(MusicVolumeMultiplier);
        }
	}

	void CollectTargets()
	{
		GetAllActorsOfClass(Targets);
	}

	void CheckWinCondition() {
		for (int i = 0 ; i < Targets.Num() ; i++) {
			ATargetActor Target = Targets[i];
			if (!Target.HasCrate()) {
				return;
			}
		}
		Print("Win");
	}
}