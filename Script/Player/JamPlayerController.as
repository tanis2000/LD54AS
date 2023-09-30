class AJamPlayerController : APlayerController
{
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY()
	UUserWidget PauseMenuInstance;

	UPROPERTY(DefaultComponent)
	UInputComponent InputComponent;

	UPROPERTY()
	AHeroPawn Hero;

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

		TArray<AHeroPawn> Heroes;
		GetAllActorsOfClass(Heroes);
		Hero = Cast<AHeroPawn>(Heroes[0]);

		// TArray<AAmbientSound> AmbientSounds;
		// GetAllActorsOfClass(AmbientSounds);
		// AAmbientSound AS = AmbientSounds[0];

		// USoundClass Effects = Cast<USoundClass>(FindObject("/Game/Audio/SC_Effects"));
	}

	UFUNCTION(BlueprintCallable)
	void MoveRight(FKey key)
	{
		Hero.MoveRight();
	}

	UFUNCTION(BlueprintCallable)
	void MoveLeft(FKey key)
	{
		Hero.MoveLeft();
	}

	UFUNCTION(BlueprintCallable)
	void MoveUp(FKey key)
	{
		Hero.MoveUp();
	}

	UFUNCTION(BlueprintCallable)
	void MoveDown(FKey key)
	{
		Hero.MoveDown();
	}
}