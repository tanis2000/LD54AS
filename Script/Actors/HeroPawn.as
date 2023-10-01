class AHeroPawn: APawn
{
    UPROPERTY(DefaultComponent, RootComponent)
    UBoxComponent Collider;

    UPROPERTY(DefaultComponent, Attach = Collider)
    USkeletalMeshComponent BaseMesh;

    UPROPERTY(DefaultComponent, Attach = Collider)
    UArrowComponent Arrow;

    UPROPERTY(DefaultComponent)
    UFloatingPawnMovement MovementComponent;

	UPROPERTY(DefaultComponent)
	UStretchComponent Stretch;

	UPROPERTY(DefaultComponent)
	UAudioComponent Audio;

    UPROPERTY()
    UCurveVector MovementInterpolationCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase> IdleSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase> MoveSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase> PushSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase> BlockedSound;

    FVector TargetLocation;

    UPROPERTY(EditAnywhere)
    float MovementSpeed = 500;

    TArray<AActor> Crates;

    FVector StartingLocation;

    UPROPERTY()
    bool bMoving;

    UPROPERTY()
    bool bPushing;

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
        PlaySounds();
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
            bMoving = false;
            bPushing = false;
            return;
        }

        bMoving = true;
        bPushing = true;

        if ((CurrentLocation - TargetLocation).GetAbs().Size() < 10) {
            SetActorLocation(TargetLocation);
            // Stretch.Squeeze();
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

    void PerformMove(FVector Direction)
    {
        if (!bMoving && !bPushing && PathIsBlocked(Direction)){
            Sound::PlayRandomSFX(Audio, BlockedSound);
        }
        if (CanMove(Direction)) {
            if (WillTryToPushCrate(Direction)) {
                Sound::PlayRandomSFX(Audio, PushSound);
            } else {
                Sound::PlayRandomSFX(Audio, MoveSound);
            }
            StartingLocation = GetActorLocation();
            FaceDirection(Direction);
            // Stretch.Stretch();
            TargetLocation = GetActorLocation() + Direction * 100;
        }
    }

    UFUNCTION()
    void MoveRight() {
        FVector Direction = FVector::RightVector;
        PerformMove(Direction);
    }

    UFUNCTION()
    void MoveLeft() {
        FVector Direction = FVector::LeftVector;
        PerformMove(Direction);
    }

    UFUNCTION()
    void MoveUp() {
        FVector Direction = FVector::ForwardVector;
        PerformMove(Direction);
    }

    UFUNCTION()
    void MoveDown() {
        FVector Direction = FVector::BackwardVector;
        PerformMove(Direction);
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

    void FaceDirection(FVector Direction)
    {
        FVector NewForward = Direction;
        NewForward.Normalize();
        FRotator Rotator = NewForward.Rotation();
        SetActorRotation(Rotator);
    }

    void PlaySounds()
    {
        if (!bMoving && !bPushing && !Audio.IsPlaying() && Math::RandRange(0.0, 1.0) < 0.003) {
            Sound::PlayRandomSFX(Audio, IdleSound);
        }
    }

    bool WillTryToPushCrate(FVector Direction) {
        FVector Start = GetActorLocation();
        FVector End = Start + Direction * 80;
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

    bool PathIsBlocked(FVector Direction) {
        FVector Start = GetActorLocation();
        FVector End = Start + Direction * 80;
        TArray<AActor> Ignore;
        Ignore.Add(this);
        FHitResult Hit;

        if(System::LineTraceSingle(Start, End, ETraceTypeQuery::Visibility, false, Ignore, EDrawDebugTrace::ForDuration, Hit, true)) {
            ACratePawn Crate = Cast<ACratePawn>(Hit.Actor);
            if (Crate != nullptr) {
                if (!Crate.CanMove(Direction)) {
                    return true;
                }
            }
        }

        if(System::LineTraceSingle(Start, End, ETraceTypeQuery::Visibility, false, Ignore, EDrawDebugTrace::ForDuration, Hit, true)) {
            AWallPawn Wall = Cast<AWallPawn>(Hit.Actor);
            if (Wall != nullptr) {
                return true;
            }
        }
        return false;
    }
}