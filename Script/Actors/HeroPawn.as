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

    FVector TargetLocation;

    UPROPERTY(EditAnywhere)
    float MovementSpeed = 500;

    TArray<AActor> Crates;

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
            return;
        }

        FVector Direction = (TargetLocation - CurrentLocation);
        Direction.Normalize();
        FVector NewLocation = CurrentLocation + (Direction * MovementSpeed * DeltaSeconds);

        FHitResult Hit;
        SetActorLocation(NewLocation, true, Hit, true); 
        // SetActorLocation(NewLocation); 
    }

    UFUNCTION()
    void MoveRight() {
        // AddMovementInput(FVector::RightVector * 100, 1, true);
        // GetMovementComponent().AddInputVector(FVector::RightVector * 100);
        if (CanMove(FVector::RightVector)) {
            TargetLocation = GetActorLocation() + FVector::RightVector * 100;
        }
    }

    UFUNCTION()
    void MoveLeft() {
        if (CanMove(FVector::LeftVector)) {
            TargetLocation = GetActorLocation() + FVector::LeftVector * 100;
        }
    }

    UFUNCTION()
    void MoveUp() {
        if (CanMove(FVector::ForwardVector)) {
            TargetLocation = GetActorLocation() + FVector::ForwardVector * 100;
        }
    }

    UFUNCTION()
    void MoveDown() {
        if (CanMove(FVector::BackwardVector)) {
            TargetLocation = GetActorLocation() + FVector::BackwardVector * 100;
        }
    }

    UFUNCTION()
	private void OnBeginOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
						UPrimitiveComponent OtherComp, int OtherBodyIndex, bool bFromSweep,
						const FHitResult&in SweepResult)
	{
        Print(f"OnBeginOverlap {OtherActor.Tags.Num()}");
	}

	UFUNCTION()
	private void OnEndOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
					  UPrimitiveComponent OtherComp, int OtherBodyIndex)
	{
        Print(f"OnEndOverlap {OtherActor.Tags.Num()}");
	}

}