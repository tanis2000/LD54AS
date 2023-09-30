class UJamGameInstance: UGameInstance
{
    UPROPERTY(Transient, Replicated)
    FText PlayerDisplayName;
    default PlayerDisplayName = FText::FromString("TestPlayer");

    UPROPERTY(BlueprintReadWrite)
    int CurrentLevel = 1;

    UFUNCTION(BlueprintCallable, Category = "Player")
    FText GetPlayerDisplayName()
    {
        return PlayerDisplayName;
    }

    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetPlayerDisplayName(FText PlayerName)
    {
        PlayerDisplayName = PlayerName;
    }
}