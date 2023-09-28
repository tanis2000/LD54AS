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

	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		Collider.OnComponentHit.AddUFunction(this, n"OnHit");
		BaseMesh.OnComponentBeginOverlap.AddUFunction(this, n"OnBeginOverlap");
		BaseMesh.OnComponentEndOverlap.AddUFunction(this, n"OnEndOverlap");
	}

	void Jump()
	{
        Print("Trying to jump");
        Collider.AddImpulse(FVector::UpVector * 500, NAME_None, true);
        Stretch.Stretch();
	}

	UFUNCTION()
	void OnHit(UPrimitiveComponent HitComponent, AActor OtherActor, UPrimitiveComponent OtherComp, FVector NormalImpulse, const FHitResult&in Hit)
	{
		//Print(f"Hit {OtherActor.Tags.Num()} {Hit.bBlockingHit}");
		//Stretch.Squeeze();
	}

	UFUNCTION()
	private void OnBeginOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
						UPrimitiveComponent OtherComp, int OtherBodyIndex, bool bFromSweep,
						const FHitResult&in SweepResult)
	{
        Print(f"OnBeginOverlap {OtherActor.Tags.Num()}");
        Stretch.Squeeze();
	}

	UFUNCTION()
	private void OnEndOverlap(UPrimitiveComponent OverlappedComponent, AActor OtherActor,
					  UPrimitiveComponent OtherComp, int OtherBodyIndex)
	{
        Print(f"OnEndOverlap {OtherActor.Tags.Num()}");
	}
}