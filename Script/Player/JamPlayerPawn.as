class AJamPlayerPawn: APawn
{
    UPROPERTY(DefaultComponent, RootComponent)
    USceneComponent SceneRoot;

    UPROPERTY(DefaultComponent, Attach = SceneRoot)
    USpringArmComponent SpringArm;

    UPROPERTY(DefaultComponent, Attach = SpringArm)
    UCameraComponent Camera;
}