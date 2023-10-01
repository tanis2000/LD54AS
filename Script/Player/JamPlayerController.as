class AJamPlayerController : APlayerController
{
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY()
	UUserWidget PauseMenuInstance;

	UPROPERTY(DefaultComponent)
	UInputComponent InputComponent;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> EndGameClass;

	UPROPERTY()
	UUserWidget EndGameInstance;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget HUDInstance;

	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu(FKey key)
	{
		if (PauseMenuInstance != nullptr && PauseMenuInstance.IsInViewport())
		{
			PauseMenuInstance.RemoveFromParent();
			PauseMenuInstance = nullptr;
			bShowMouseCursor = false;
			Widget::SetInputMode_GameOnly(this);
			Gameplay::SetGamePaused(false);

			AJamGameMode GameMode = Cast<AJamGameMode>(Gameplay::GetGameMode());
			GameMode.WriteSaveGame();
			return;
		}

		PauseMenuInstance = WidgetBlueprint::CreateWidget(PauseMenuClass, this);
		if (PauseMenuInstance != nullptr)
		{
			PauseMenuInstance.AddToViewport(100);
			bShowMouseCursor = true;
			Widget::SetInputMode_UIOnlyEx(this);
			Gameplay::SetGamePaused(true);
		}
	}

	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		PushInputComponent(InputComponent);
		InputComponent.BindAction(n"PauseMenu", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"TogglePauseMenu"));
		InputComponent.BindAction(n"MoveRight", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"MoveRight"));
		InputComponent.BindAction(n"MoveLeft", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"MoveLeft"));
		InputComponent.BindAction(n"MoveUp", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"MoveUp"));
		InputComponent.BindAction(n"MoveDown", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"MoveDown"));
		InputComponent.BindAction(n"Restart", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"Restart"));
		InputComponent.BindAction(n"Skip", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"Skip"));
		InputComponent.BindAction(n"Previous", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"Previous"));

		// HUDInstance = WidgetBlueprint::CreateWidget(HUDClass, this);
		// HUDInstance.AddToViewport();
		
		// TArray<AAmbientSound> AmbientSounds;
		// GetAllActorsOfClass(AmbientSounds);
		// AAmbientSound AS = AmbientSounds[0];

		// USoundClass Effects = Cast<USoundClass>(FindObject("/Game/Audio/SC_Effects"));
	}

	AHeroPawn GetHero()
	{
		AHeroPawn Hero = nullptr;
		TArray<AHeroPawn> Heroes;
		GetAllActorsOfClass(Heroes);
		if (Heroes.Num() > 0) {
			Hero = Cast<AHeroPawn>(Heroes[0]);
		}
		return Hero;
	}

	UFUNCTION(BlueprintCallable)
	void MoveRight(FKey key)
	{
		AHeroPawn Hero = GetHero();
		if (Hero != nullptr) {
			Hero.MoveRight();
		}
	}

	UFUNCTION(BlueprintCallable)
	void MoveLeft(FKey key)
	{
		AHeroPawn Hero = GetHero();
		if (Hero != nullptr) {
			Hero.MoveLeft();
		}
	}

	UFUNCTION(BlueprintCallable)
	void MoveUp(FKey key)
	{
		AHeroPawn Hero = GetHero();
		if (Hero != nullptr) {
			Hero.MoveUp();
		}
	}

	UFUNCTION(BlueprintCallable)
	void MoveDown(FKey key)
	{
		AHeroPawn Hero = GetHero();
		if (Hero != nullptr) {
			Hero.MoveDown();
		}
	}

	UFUNCTION(BlueprintCallable)
	void Restart(FKey key)
	{
		AJamGameMode GameMode = Cast<AJamGameMode>(Gameplay::GetGameMode());
		GameMode.RestartLevel();
	}

	UFUNCTION(BlueprintCallable)
	void Skip(FKey key)
	{
		AJamGameMode GameMode = Cast<AJamGameMode>(Gameplay::GetGameMode());
		GameMode.SkipLevel();
	}

	UFUNCTION(BlueprintCallable)
	void Previous(FKey key)
	{
		AJamGameMode GameMode = Cast<AJamGameMode>(Gameplay::GetGameMode());
		GameMode.PreviousLevel();
	}

	void ShowEndGame()
	{
		// HUDInstance.RemoveFromParent();
		EndGameInstance = WidgetBlueprint::CreateWidget(EndGameClass, this);
		EndGameInstance.AddToViewport();
		bShowMouseCursor = true;
		Widget::SetInputMode_UIOnlyEx(this);
		Gameplay::SetGamePaused(true);
	}

	UFUNCTION(BlueprintCallable)
	void HideEndGame()
	{
		if (EndGameInstance != nullptr) {
			EndGameInstance.RemoveFromParent();
			EndGameInstance = nullptr;
			bShowMouseCursor = false;
			Widget::SetInputMode_GameAndUIEx(this);
			Gameplay::SetGamePaused(false);
		}
	}
}