class ATestAIController : AAIController
{
	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		Log("Hi from the AI");
		System::SetTimer(this, n"Think", 3.0, bLooping = true);
	}

	UFUNCTION()
	void Think()
	{
        Log("AI is thinking");
		ATestActor Pawn = Cast<ATestActor>(GetControlledPawn());
		Pawn.Jump();
	}
}