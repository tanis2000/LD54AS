class AFigurineActor : AActor
{
    UPROPERTY(DefaultComponent, RootComponent)
    USkeletalMeshComponent BaseMesh;

    UPROPERTY(DefaultComponent)
    URotatingMovementComponent RotatingMovement;
}