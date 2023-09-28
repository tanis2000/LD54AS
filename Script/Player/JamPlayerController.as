class AJamPlayerController : APlayerController
{
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY()
	UUserWidget PauseMenuInstance;

	UPROPERTY(DefaultComponent)
	UInputComponent InputComponent;

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

		// TArray<AAmbientSound> AmbientSounds;
		// GetAllActorsOfClass(AmbientSounds);
		// AAmbientSound AS = AmbientSounds[0];

		// USoundClass Effects = Cast<USoundClass>(FindObject("/Game/Audio/SC_Effects"));
	}
}