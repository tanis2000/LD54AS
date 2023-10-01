class ACratePawn: APawn
{
    UPROPERTY(DefaultComponent, RootComponent)
    UBoxComponent Collider;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UStaticMeshComponent BaseMesh;

    UPROPERTY(Category = "Game")
    UMaterialInstance BaseMaterial;

    UPROPERTY(Category = "Game")
    UMaterialInstance TriggeredMaterial;

    UPROPERTY(EditAnywhere)
    float MovementSpeed = 500;

    FVector TargetLocation;
    

    default SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        TargetLocation = GetActorLocation();

        BaseMesh.OnComponentBeginOverlap.AddUFunction(this, n"OnBeginOverlap");
		BaseMesh.OnComponentEndOverlap.AddUFunction(this, n"OnEndOverlap");
    }

    UFUNCTION(BlueprintOverride)
    void Tick(float DeltaSeconds)
    {
        Move(DeltaSeconds);
        if (IsOnTarget()) {
            BaseMesh.SetMaterial(0, TriggeredMaterial);
        } else {
            BaseMesh.SetMaterial(0, BaseMaterial);
        }
    }

    bool CanMove(FVector Direction) {
        FVector CurrentLocation = GetActorLocation();
        if (CurrentLocation != TargetLocation) {
            return false;
        }

        FVector Start = GetActorLocation();
        FVector End = Start + Direction * 80;
        TArray<AActor> Ignore;
        Ignore.Add(this);
        FHitResult Hit;

        if(System::LineTraceSingle(Start, End, ETraceTypeQuery::Visibility, false, Ignore, EDrawDebugTrace::ForDuration, Hit, true)) {
            return false;
        }
        return true;
    }

    void Move(float DeltaSeconds)
    {
        FVector CurrentLocation = GetActorLocation();
        if (CurrentLocation == TargetLocation) {
            return;
        }

        if ((CurrentLocation - TargetLocation).GetAbs().Size() < 10) {
            SetActorLocation(TargetLocation);
            return;
        }

        FVector Direction = (TargetLocation - CurrentLocation);
        Direction.Normalize();
        FVector NewLocation = CurrentLocation + (Direction * MovementSpeed * DeltaSeconds);

        FHitResult Hit;
        // SetActorLocation(NewLocation, true, Hit, true); 
        SetActorLocation(NewLocation); 
    }

    UFUNCTION()
	private void OnBeginOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
						UPrimitiveComponent OtherComp, int OtherBodyIndex, bool bFromSweep,
						const FHitResult&in SweepResult)
	{
        if (OtherActor != this) {
            Log(f"Crate OnBeginOverlap {OtherActor.Class}");

            AHeroPawn Hero = Cast<AHeroPawn>(OtherActor);
            if (Hero != nullptr) {
                Log(f">> {SweepResult.ImpactNormal}");
                if (CanMove(SweepResult.ImpactNormal)) {
                    TargetLocation = GetActorLocation() + SweepResult.ImpactNormal * 100;
                }
            }
        }
	}

	UFUNCTION()
	private void OnEndOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
					  UPrimitiveComponent OtherComp, int OtherBodyIndex)
	{
        // Log(f"OnEndOverlap {OtherActor.Tags.Num()}");
	}

    bool IsOnTarget() {
        FVector Start = GetActorLocation();
        FVector End = Start + FVector::DownVector * 100;
        TArray<AActor> Ignore;
        Ignore.Add(this);
        FHitResult Hit;

        if(System::LineTraceSingle(Start, End, ETraceTypeQuery::Visibility, false, Ignore, EDrawDebugTrace::ForDuration, Hit, true)) {
            ATargetActor Target = Cast<ATargetActor>(Hit.Actor);
            if (Target != nullptr) {
                return true;
            }
            return false;
        }
        return false;
    }
}