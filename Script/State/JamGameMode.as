enum EGameState {
	Initializing,
	Transitioning,
	Playing,
	End,
}
class AJamGameMode : AGameModeBase
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicVolumeMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SoundEffectsVolumeMultiplier = 1;

	UPROPERTY()
	UJamSaveGame CurrentSaveGame;
	default CurrentSaveGame = UJamSaveGame();

	UPROPERTY()
	EGameState CurrentGameState;

	default PlayerStateClass = AJamPlayerState::StaticClass();
	default PlayerControllerClass = AJamPlayerController::StaticClass();

	TArray<ATargetActor> Targets;
	TArray<AHeroPawn> Heroes;
	TArray<AWallPawn> Walls;
	TArray<ACratePawn> Crates;

	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		CurrentGameState = EGameState::Initializing;
		UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
		ReadSaveGame();
		UpdateAudioVolumes();
		GetGridGen().Initialize();
		GenerateLevel(GI.CurrentLevel);
		CollectTargets();
	}

	UFUNCTION(BlueprintOverride)
	void Tick(float DeltaSeconds)
	{
		switch(CurrentGameState) {
			case EGameState::Playing:
				CheckWinCondition();
				break;
			case EGameState::Transitioning:
				CheckEndGame();
				NextLevel();
				break;
			case EGameState::End:
				ShowEndGame();
				break;
		}

	}

	void WriteSaveGame()
	{
		UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
		CurrentSaveGame = UJamSaveGame();
		CurrentSaveGame.MusicVolumeMultiplier = MusicVolumeMultiplier;
		CurrentSaveGame.SoundEffectsVolumeMultiplier = SoundEffectsVolumeMultiplier;
		CurrentSaveGame.CurrentLevel = GI.CurrentLevel;
		Gameplay::SaveGameToSlot(CurrentSaveGame, "Slot1", 0);
		Log("Save game created");
	}

	void ReadSaveGame()
	{
		if (Gameplay::DoesSaveGameExist("Slot1", 0))
		{
			UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
			CurrentSaveGame = Cast<UJamSaveGame>(Gameplay::LoadGameFromSlot("Slot1", 0));
			MusicVolumeMultiplier = CurrentSaveGame.MusicVolumeMultiplier;
			SoundEffectsVolumeMultiplier = CurrentSaveGame.SoundEffectsVolumeMultiplier;
			GI.CurrentLevel = CurrentSaveGame.CurrentLevel;
			Log("Save game loaded");
		}
		else
		{
			Log("No save game found");
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
		Targets.Reset();
		Heroes.Reset();
		Walls.Reset();
		Crates.Reset();
		GetAllActorsOfClass(Targets);
		GetAllActorsOfClass(Heroes);
		GetAllActorsOfClass(Walls);
		GetAllActorsOfClass(Crates);
	}

	void CheckWinCondition() {
		if (CurrentGameState != EGameState::Playing) {
			return;
		}

		for (int i = 0 ; i < Targets.Num() ; i++) {
			ATargetActor Target = Targets[i];
			if (!Target.HasCrate()) {
				return;
			}
		}
		Log("Win");
		
		CurrentGameState = EGameState::Transitioning;
		UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
		SubmitScore(GI.CurrentLevel);
		GI.CurrentLevel++;
		WriteSaveGame();
	}

	void NextLevel() {
		UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
		CleanUp();
		GenerateLevel(GI.CurrentLevel);
		CollectTargets();
	}

	AGridGen GetGridGen()
	{
		TArray<AGridGen> GridGens;
		GetAllActorsOfClass(GridGens);
		AGridGen GridGen = GridGens[0];
		return GridGen;
	}

	void GenerateLevel(int LevelNumber)
	{
		AGridGen GridGen = GetGridGen();
		if (LevelNumber > GridGen.NumLevels()) {
			return;
		}
		FGrid G = Grid::ParseLevel(GridGen.GridFromNumber(LevelNumber));
		GridGen.GenerateLevel(G);
		CurrentGameState = EGameState::Playing;
	}

	void SubmitScore(int Score)
	{
		UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
		TArray<ALeaderboardActor> Leaderboards;
		GetAllActorsOfClass(Leaderboards);
		ALeaderboardActor Leaderboard = Leaderboards[0];
		Leaderboard.SubmitScore(GI.PlayerDisplayName.ToString(), Score);
	}

	void CleanUp() {
		for (int i = 0 ; i < Targets.Num() ; i++) {
			AActor Actor = Targets[i];
			Actor.DestroyActor();
		}
		for (int i = 0 ; i < Heroes.Num() ; i++) {
			AActor Actor = Heroes[i];
			Actor.DestroyActor();
		}
		for (int i = 0 ; i < Walls.Num() ; i++) {
			AActor Actor = Walls[i];
			Actor.DestroyActor();
		}
		for (int i = 0 ; i < Crates.Num() ; i++) {
			AActor Actor = Crates[i];
			Actor.DestroyActor();
		}
	}

	void RestartLevel()
	{
		CurrentGameState = EGameState::Transitioning;
		NextLevel();
	}

	void SkipLevel()
	{
		CurrentGameState = EGameState::Transitioning;
		UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
		GI.CurrentLevel++;
	}

	void PreviousLevel()
	{
		CurrentGameState = EGameState::Transitioning;
		UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
		if (GI.CurrentLevel > 1) {
			GI.CurrentLevel--;
		}
	}

	void CheckEndGame()
	{
		UJamGameInstance GI = Cast<UJamGameInstance>(GameInstance);
		AGridGen GridGen = GetGridGen();
		if (GI.CurrentLevel > GridGen.NumLevels()) {
			CurrentGameState = EGameState::End;
		}
		
	}

	void ShowEndGame() 
	{
		AJamPlayerController PC = Cast<AJamPlayerController>(Gameplay::GetPlayerController(0));
		PC.ShowEndGame();
	}
}