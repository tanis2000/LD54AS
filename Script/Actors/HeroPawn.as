class AHeroPawn: APawn
{
    UPROPERTY(DefaultComponent, RootComponent)
    UBoxComponent Collider;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UStaticMeshComponent BaseMesh;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UArrowComponent Arrow;

    UPROPERTY(DefaultComponent)
    UFloatingPawnMovement MovementComponent;

	UPROPERTY(DefaultComponent)
	UStretchComponent Stretch;

    UPROPERTY()
    UCurveVector MovementInterpolationCurve;

    FVector TargetLocation;

    UPROPERTY(EditAnywhere)
    float MovementSpeed = 500;

    TArray<AActor> Crates;

    FVector StartingLocation;

    default SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        
        TargetLocation = GetActorLocation();

        BaseMesh.OnComponentBeginOverlap.AddUFunction(this, n"OnBeginOverlap");
		BaseMesh.OnComponentEndOverlap.AddUFunction(this, n"OnEndOverlap");

        GetMovementComponent().UpdatedComponent = RootComponent;

        GetAllActorsOfClass(ACratePawn::StaticClass(), Crates);
    }

    UFUNCTION(BlueprintOverride)
    void Tick(float DeltaSeconds)
    {
        Move(DeltaSeconds);
    }

    void GridMove() {

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
            ACratePawn Crate = Cast<ACratePawn>(Hit.Actor);
            if (Crate != nullptr) {
                if (Crate.CanMove(Direction)) {
                    return true;
                }
            }
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
            Stretch.Squeeze();
            return;
        }

        FVector Direction = (TargetLocation - CurrentLocation);
        Direction.Normalize();
        FVector TotalDistance = TargetLocation - StartingLocation;
        FVector ActualDistance = TargetLocation - CurrentLocation;
        float Diff = ActualDistance.Size() / TotalDistance.Size();
        FVector InterpOffset = MovementInterpolationCurve.GetVectorValue(Diff);
        FVector NewLocation = CurrentLocation + (Direction * MovementSpeed * DeltaSeconds) * InterpOffset;

        FHitResult Hit;
        SetActorLocation(NewLocation, true, Hit, true); 
        // SetActorLocation(NewLocation); 
    }

    UFUNCTION()
    void MoveRight() {
        if (CanMove(FVector::RightVector)) {
            StartingLocation = GetActorLocation();
            Stretch.Stretch();
            TargetLocation = GetActorLocation() + FVector::RightVector * 100;
        }
    }

    UFUNCTION()
    void MoveLeft() {
        if (CanMove(FVector::LeftVector)) {
            StartingLocation = GetActorLocation();
            Stretch.Stretch();
            TargetLocation = GetActorLocation() + FVector::LeftVector * 100;
        }
    }

    UFUNCTION()
    void MoveUp() {
        if (CanMove(FVector::ForwardVector)) {
            StartingLocation = GetActorLocation();
            Stretch.Stretch();
            TargetLocation = GetActorLocation() + FVector::ForwardVector * 100;
        }
    }

    UFUNCTION()
    void MoveDown() {
        if (CanMove(FVector::BackwardVector)) {
            StartingLocation = GetActorLocation();
            Stretch.Stretch();
            TargetLocation = GetActorLocation() + FVector::BackwardVector * 100;
        }
    }

    UFUNCTION()
	private void OnBeginOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
						UPrimitiveComponent OtherComp, int OtherBodyIndex, bool bFromSweep,
						const FHitResult&in SweepResult)
	{
        Log(f"OnBeginOverlap {OtherActor.Tags.Num()}");
	}

	UFUNCTION()
	private void OnEndOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
					  UPrimitiveComponent OtherComp, int OtherBodyIndex)
	{
        Log(f"OnEndOverlap {OtherActor.Tags.Num()}");
	}

}