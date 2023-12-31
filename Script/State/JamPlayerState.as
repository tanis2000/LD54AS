class AJamPlayerState: APlayerState
{
    // TODO Remove all this stuff, it is in JamGameInstance now

    UPROPERTY(Transient, Replicated)
    FText PlayerDisplayName;

    UFUNCTION(BlueprintCallable, Category = "Player")
    FText GetPlayerDisplayName()
    {
        return PlayerDisplayName;
    }

    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetPlayerDisplayName(FText Name)
    {
        PlayerDisplayName = Name;
    }
}