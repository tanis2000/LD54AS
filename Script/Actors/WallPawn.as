class AWallPawn: APawn
{
    UPROPERTY(DefaultComponent, RootComponent)
    UBoxComponent Collider;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UStaticMeshComponent BaseMesh;

    default SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

}