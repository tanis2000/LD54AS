class AMenuGameModeBase : AGameModeBase
{
    default PlayerStateClass = AJamPlayerState::StaticClass();
	default PlayerControllerClass = AJamPlayerController::StaticClass();

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        UJamSaveSystem SaveSystem = UJamSaveSystem::Get();
        
    }
}