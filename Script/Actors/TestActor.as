class ATestActor : APawn
{
	UPROPERTY(DefaultComponent, RootComponent)
	USceneComponent SceneRoot;

	UPROPERTY(DefaultComponent, Attach = SceneRoot)
	UBoxComponent Collider;

	UPROPERTY(DefaultComponent, Attach = Collider)
	UStaticMeshComponent BaseMesh;

	UPROPERTY(DefaultComponent, Attach = BaseMesh)
	UArrowComponent GroundCheckAttachment;

	UPROPERTY(DefaultComponent, Attach = BaseMesh)
	UGroundCheckComponent GroundCheck;

	UPROPERTY(DefaultComponent)
	UStretchComponent Stretch;

    UPROPERTY(DefaultComponent)
    UInputComponent InputComponent;

	UPROPERTY(DefaultComponent)
	UAudioComponent Audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundWave JumpSound;

	AJamGameMode GameMode;

	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		Collider.OnComponentHit.AddUFunction(this, n"OnHit");
		BaseMesh.OnComponentBeginOverlap.AddUFunction(this, n"OnBeginOverlap");
		BaseMesh.OnComponentEndOverlap.AddUFunction(this, n"OnEndOverlap");

		GameMode = Cast<AJamGameMode>(Gameplay::GetGameMode());
	}

	void Jump()
	{
        Log("Trying to jump");
        Collider.AddImpulse(FVector::UpVector * 500, NAME_None, true);
        Stretch.Stretch();
		Sound::PlaySFX(Audio, JumpSound);
		// Audio.SetSound(JumpSound);
		// Audio.SetVolumeMultiplier(GameMode.SoundEffectsVolumeMultiplier);
		// Audio.Play();
	}

	UFUNCTION()
	void OnHit(UPrimitiveComponent HitComponent, AActor OtherActor, UPrimitiveComponent OtherComp, FVector NormalImpulse, const FHitResult&in Hit)
	{
		//Log(f"Hit {OtherActor.Tags.Num()} {Hit.bBlockingHit}");
		//Stretch.Squeeze();
	}

	UFUNCTION()
	private void OnBeginOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
						UPrimitiveComponent OtherComp, int OtherBodyIndex, bool bFromSweep,
						const FHitResult&in SweepResult)
	{
        // Log(f"OnBeginOverlap {OtherActor.Tags.Num()}");
        Stretch.Squeeze();
	}

	UFUNCTION()
	private void OnEndOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
					  UPrimitiveComponent OtherComp, int OtherBodyIndex)
	{
        // Log(f"OnEndOverlap {OtherActor.Tags.Num()}");
	}
}