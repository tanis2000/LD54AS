class ATargetActor: AActor
{
    UPROPERTY(DefaultComponent, RootComponent)
    UBoxComponent Collider;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UStaticMeshComponent BaseMesh;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UNiagaraComponent Particles;

    UPROPERTY()
    UMaterialInstance BaseMaterial;

    UPROPERTY()
    UMaterialInstance TriggeredMaterial;

    default SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    UFUNCTION(BlueprintOverride)
    void Tick(float DeltaSeconds)
    {
        if (HasCrate()) {
            BaseMesh.SetMaterial(0, TriggeredMaterial);
        } else {
            BaseMesh.SetMaterial(0, BaseMaterial);
        }
    }

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