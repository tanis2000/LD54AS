// Copyright(C)2023 Valerio Santinelli


#include "JamPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LD54AS/Actors/HeroPawn.h"
#include "LD54AS/State/JamGameMode.h"


void AJamPlayerController2::TogglePauseMenu(FKey key)
	{
		if (PauseMenuInstance != nullptr && PauseMenuInstance->IsInViewport())
		{
			PauseMenuInstance->RemoveFromParent();
			PauseMenuInstance = nullptr;
			bShowMouseCursor = false;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
			UGameplayStatics::SetGamePaused(GetWorld(), false);

			AJamGameMode2 *GameMode = Cast<AJamGameMode2>(UGameplayStatics::GetGameMode(GetWorld()));
			GameMode->WriteSaveGame();
			return;
		}

		PauseMenuInstance = UWidgetBlueprintLibrary::Create(GetWorld(), PauseMenuClass, this);
		if (PauseMenuInstance != nullptr)
		{
			PauseMenuInstance->AddToViewport(100);
			bShowMouseCursor = true;
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
	}

	
	void AJamPlayerController2::BeginPlay()
	{
		PushInputComponent(InputComponent);
		InputComponent->BindAction("PauseMenu", EInputEvent::IE_Pressed, this, &AJamPlayerController2::TogglePauseMenu);
		InputComponent->BindAction("MoveRight", EInputEvent::IE_Pressed, this, &AJamPlayerController2::MoveRight);
		InputComponent->BindAction("MoveLeft", EInputEvent::IE_Pressed, this, &AJamPlayerController2::MoveLeft);
		InputComponent->BindAction("MoveUp", EInputEvent::IE_Pressed, this, &AJamPlayerController2::MoveUp);
		InputComponent->BindAction("MoveDown", EInputEvent::IE_Pressed, this, &AJamPlayerController2::MoveDown);
		InputComponent->BindAction("Restart", EInputEvent::IE_Pressed, this, &AJamPlayerController2::Restart);
		InputComponent->BindAction("Skip", EInputEvent::IE_Pressed, this, &AJamPlayerController2::Skip);
		InputComponent->BindAction("Previous", EInputEvent::IE_Pressed, this, &AJamPlayerController2::Previous);

		// HUDInstance = WidgetBlueprint::CreateWidget(HUDClass, this);
		// HUDInstance.AddToViewport();
		
		// TArray<AAmbientSound> AmbientSounds;
		// GetAllActorsOfClass(AmbientSounds);
		// AAmbientSound AS = AmbientSounds[0];

		// USoundClass Effects = Cast<USoundClass>(FindObject("/Game/Audio/SC_Effects"));
	}

	AHeroPawn2 *AJamPlayerController2::GetHero()
	{
		AHeroPawn2 *Hero = nullptr;
		TArray<AActor *> Heroes;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHeroPawn2::StaticClass(), Heroes);
		if (Heroes.Num() > 0) {
			Hero = Cast<AHeroPawn2>(Heroes[0]);
		}
		return Hero;
	}

	
	void AJamPlayerController2::MoveRight(FKey key)
	{
		AHeroPawn2 *Hero = GetHero();
		if (Hero != nullptr) {
			Hero->MoveRight();
		}
	}

	void AJamPlayerController2::MoveLeft(FKey key)
	{
		AHeroPawn2 *Hero = GetHero();
		if (Hero != nullptr) {
			Hero->MoveLeft();
		}
	}

	void AJamPlayerController2::MoveUp(FKey key)
	{
		AHeroPawn2 *Hero = GetHero();
		if (Hero != nullptr) {
			Hero->MoveUp();
		}
	}

	
	void AJamPlayerController2::MoveDown(FKey key)
	{
		AHeroPawn2 *Hero = GetHero();
		if (Hero != nullptr) {
			Hero->MoveDown();
		}
	}

	void AJamPlayerController2::Restart(FKey key)
	{
		AJamGameMode2 *GameMode = Cast<AJamGameMode2>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartLevel();
	}

	void AJamPlayerController2::Skip(FKey key)
	{
		AJamGameMode2 *GameMode = Cast<AJamGameMode2>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->SkipLevel();
	}

	void AJamPlayerController2::Previous(FKey key)
	{
		AJamGameMode2 *GameMode = Cast<AJamGameMode2>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->PreviousLevel();
	}

	void AJamPlayerController2::ShowEndGame()
	{
		// HUDInstance.RemoveFromParent();
		EndGameInstance = UWidgetBlueprintLibrary::Create(GetWorld(), EndGameClass, this);
		EndGameInstance->AddToViewport();
		bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	void AJamPlayerController2::HideEndGame()
	{
		if (EndGameInstance != nullptr) {
			EndGameInstance->RemoveFromParent();
			EndGameInstance = nullptr;
			bShowMouseCursor = false;
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this);
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}
	}