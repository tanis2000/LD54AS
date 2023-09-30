class AWallPawn: APawn
{
    UPROPERTY(DefaultComponent, RootComponent)
    UBoxComponent Collider;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UStaticMeshComponent BaseMesh;

    // UFUNCTION(BlueprintOverride)
    // void BeginPlay()
    // {
    //     UPaperTileMap Map;
    //     TObjectPtr<UPaperTileLayer> Layer = Map.TileLayers[0];
    //     UPaperTileLayer PL = Layer.Get();
        
    // }
}