class UGroundCheckComponent : USceneComponent
{
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bWasOnGround = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GroundProbeLength = 5.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent GroundChecker;

	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		GroundChecker = Cast<UArrowComponent>(Owner.GetComponentByClass(UArrowComponent::StaticClass()));
	}

	UFUNCTION(BlueprintOverride)
	void Tick(float DeltaSeconds)
	{
		bWasOnGround = bIsOnGround;
		bIsOnGround = IsOnGround();
	}

	bool IsOnGround()
	{
		// Log(f"Owner {Owner.GetName()}");
		FHitResult Hit;
		FVector Start = GroundChecker.GetWorldLocation();
		FVector End = Start;
		End.Z -= GroundProbeLength;
		// Log(f"Start {Start}");

		System::DrawDebugLine(Start, End, FLinearColor::Green, 1, 5);
		if (System::LineTraceSingle(Start, End, ETraceTypeQuery::Visibility, false, TArray<AActor>(), EDrawDebugTrace::ForOneFrame, Hit, true))
		// if (System::LineTraceSingleByProfile(Start, End, FName("Ground"), false, TArray<AActor>(), EDrawDebugTrace::ForOneFrame, Hit, true))
		{
			// Log(f"Trace hit {Hit.GetComponent().GetFullName()}");
			return true;
		}

		return false;
	}
	bool GetIsOnGround()
	{
		return bIsOnGround;
	}

	bool GetWasOnGround()
	{
		return bWasOnGround;
	}
}