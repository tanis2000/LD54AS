// Copyright(C)2023 Valerio Santinelli


#include "JamPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LD54AS/Actors/HeroPawn.h"
#include "LD54AS/State/JamGameMode.h"


void AJamPlayerController::TogglePauseMenu(FKey key)
	{
		if (PauseMenuInstance != nullptr && PauseMenuInstance->IsInViewport())
		{
			PauseMenuInstance->RemoveFromParent();
			PauseMenuInstance = nullptr;
			bShowMouseCursor = false;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
			UGameplayStatics::SetGamePaused(GetWorld(), false);

			AJamGameMode *GameMode = Cast<AJamGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
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

	void AJamPlayerController::BeginPlay()
	{
		PushInputComponent(InputComponent);
		InputComponent->BindAction("PauseMenu", EInputEvent::IE_Pressed, this, &AJamPlayerController::TogglePauseMenu);
		// InputComponent->BindAction("MoveRight", EInputEvent::IE_Pressed, this, &AJamPlayerController::MoveRight);
		// InputComponent->BindAction("MoveLeft", EInputEvent::IE_Pressed, this, &AJamPlayerController::MoveLeft);
		// InputComponent->BindAction("MoveUp", EInputEvent::IE_Pressed, this, &AJamPlayerController::MoveUp);
		// InputComponent->BindAction("MoveDown", EInputEvent::IE_Pressed, this, &AJamPlayerController::MoveDown);
		InputComponent->BindAction("Restart", EInputEvent::IE_Pressed, this, &AJamPlayerController::Restart);
		InputComponent->BindAction("Skip", EInputEvent::IE_Pressed, this, &AJamPlayerController::Skip);
		InputComponent->BindAction("Previous", EInputEvent::IE_Pressed, this, &AJamPlayerController::Previous);
	InputComponent->BindAxis("MoveH", this, &AJamPlayerController::MoveHorizontally);
	InputComponent->BindAxis("MoveV", this, &AJamPlayerController::MoveVertically);

		// HUDInstance = WidgetBlueprint::CreateWidget(HUDClass, this);
		// HUDInstance.AddToViewport();
		
		// TArray<AAmbientSound> AmbientSounds;
		// GetAllActorsOfClass(AmbientSounds);
		// AAmbientSound AS = AmbientSounds[0];

		// USoundClass Effects = Cast<USoundClass>(FindObject("/Game/Audio/SC_Effects"));
	}

	AHeroPawn *AJamPlayerController::GetHero()
	{
		AHeroPawn *Hero = nullptr;
		TArray<AActor *> Heroes;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHeroPawn::StaticClass(), Heroes);
		if (Heroes.Num() > 0) {
			Hero = Cast<AHeroPawn>(Heroes[0]);
		}
		return Hero;
	}

void AJamPlayerController::MoveHorizontally(float X)
{
	AHeroPawn *Hero = GetHero();
	if (Hero != nullptr) {
		if (X > 0)
		{
			Hero->MoveRight();
		} else if (X < 0)
		{
			Hero->MoveLeft();
		}
	}
}

void AJamPlayerController::MoveVertically(float Y)
{
	AHeroPawn *Hero = GetHero();
	if (Hero != nullptr) {
		if (Y > 0)
		{
			Hero->MoveUp();
		} else if (Y < 0)
		{
			Hero->MoveDown();
		}
	}
}

	void AJamPlayerController::MoveRight(FKey key)
	{
		AHeroPawn *Hero = GetHero();
		if (Hero != nullptr) {
			Hero->MoveRight();
		}
	}

	void AJamPlayerController::MoveLeft(FKey key)
	{
		AHeroPawn *Hero = GetHero();
		if (Hero != nullptr) {
			Hero->MoveLeft();
		}
	}

	void AJamPlayerController::MoveUp(FKey key)
	{
		AHeroPawn *Hero = GetHero();
		if (Hero != nullptr) {
			Hero->MoveUp();
		}
	}

	
	void AJamPlayerController::MoveDown(FKey key)
	{
		AHeroPawn *Hero = GetHero();
		if (Hero != nullptr) {
			Hero->MoveDown();
		}
	}

	void AJamPlayerController::Restart(FKey key)
	{
		AJamGameMode *GameMode = Cast<AJamGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->RestartLevel();
	}

	void AJamPlayerController::Skip(FKey key)
	{
		AJamGameMode *GameMode = Cast<AJamGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->SkipLevel();
	}

	void AJamPlayerController::Previous(FKey key)
	{
		AJamGameMode *GameMode = Cast<AJamGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->PreviousLevel();
	}

	void AJamPlayerController::ShowEndGame()
	{
		// HUDInstance.RemoveFromParent();
		EndGameInstance = UWidgetBlueprintLibrary::Create(GetWorld(), EndGameClass, this);
		EndGameInstance->AddToViewport();
		bShowMouseCursor = true;
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	void AJamPlayerController::HideEndGame()
	{
		if (EndGameInstance != nullptr) {
			EndGameInstance->RemoveFromParent();
			EndGameInstance = nullptr;
			bShowMouseCursor = false;
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this);
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}
	}