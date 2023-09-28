class UStretchComponent : UActorComponent
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector SqueezeCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector StretchCurve;

	UTimelineComponent SqueezeTimeline;
	UTimelineComponent StretchTimeline;
	FOnTimelineVector ProgressSqueezeTimeline;
	FOnTimelineVector ProgressStretchTimeline;
	FVector InitialScale;
	UStaticMeshComponent BaseMesh;
	UGroundCheckComponent GroundCheck;

	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		BaseMesh = Cast<UStaticMeshComponent>(Owner.GetComponentByClass(UStaticMeshComponent::StaticClass()));
		InitialScale = BaseMesh.GetRelativeScale3D();

		GroundCheck = Cast<UGroundCheckComponent>(Owner.GetComponentByClass(UGroundCheckComponent::StaticClass()));

		ProgressSqueezeTimeline.BindUFunction(this, FName("ProgressSqueeze"));
		ProgressStretchTimeline.BindUFunction(this, FName("ProgressStretch"));

		SqueezeTimeline = UTimelineComponent(Owner, n"SqueezeTimeline");
		StretchTimeline = UTimelineComponent(Owner, n"StretchTimeline");

		if (SqueezeCurve == nullptr)
		{
			PrintError("You must set a curve for squeezing");
		}
		else
		{
			SqueezeTimeline.AddInterpVector(SqueezeCurve, ProgressSqueezeTimeline);
		}

		if (SqueezeCurve == nullptr)
		{
			PrintError("You must set a curve for stretching");
		}
		else
		{
			StretchTimeline.AddInterpVector(StretchCurve, ProgressStretchTimeline);
		}
	}

	UFUNCTION(BlueprintOverride)
	void Tick(float DeltaSeconds)
	{
		// if (!GroundCheck.GetIsOnGround() && GroundCheck.GetWasOnGround())
		// {
		// 	Print("Started flying");
		// 	Stretch();
		// }
		// else if (GroundCheck.GetIsOnGround() && !GroundCheck.GetWasOnGround())
		// {
		// 	Print("Landed");
		// 	Squeeze();
		// }
	}

	void Stretch()
	{
		Log("Stretch");
		if (StretchTimeline.IsPlaying())
		{
			Log("Waiting for the stretch animation to finish");
			return;
		}
		SqueezeTimeline.Stop();
		StretchTimeline.PlayFromStart();
	}

	void Squeeze()
	{
		Log("Squeeze");
		if (SqueezeTimeline.IsPlaying())
		{
			Log("Waiting for the squeeze animation to finish");
			return;
		}
		StretchTimeline.Stop();
		SqueezeTimeline.PlayFromStart();
	}

	UFUNCTION()
	void ProgressSqueeze(FVector Value)
	{
		// Log(f"Squeeze progress {Value}");
		FVector Scale = InitialScale;
		Scale *= Value;
		BaseMesh.SetRelativeScale3D(Scale);
	}

	UFUNCTION()
	void ProgressStretch(FVector Value)
	{
		// Log(f"Stretch progress {Value}");
		FVector Scale = InitialScale;
		Scale *= Value;
		BaseMesh.SetRelativeScale3D(Scale);
	}
}