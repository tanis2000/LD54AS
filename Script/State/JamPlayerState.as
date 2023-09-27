class AJamPlayerState: APlayerState
{
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