class ATargetActor: AActor
{
    UPROPERTY(DefaultComponent, RootComponent)
    UBoxComponent Collider;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UStaticMeshComponent BaseMesh;

    default SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    bool HasCrate() {
        FVector Start = GetActorLocation();
        FVector End = Start + FVector::UpVector;
        TArray<AActor> Ignore;
        Ignore.Add(this);
        FHitResult Hit;

        if(System::LineTraceSingle(Start, End, ETraceTypeQuery::Visibility, false, Ignore, EDrawDebugTrace::ForDuration, Hit, true)) {
            ACratePawn Crate = Cast<ACratePawn>(Hit.Actor);
            if (Crate != nullptr) {
                return true;
            }
            return false;
        }
        return false;
    }
}