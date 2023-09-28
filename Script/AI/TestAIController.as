class ATestAIController : AAIController
{
	UFUNCTION(BlueprintOverride)
	void BeginPlay()
	{
		Print("Hi from the AI");
		System::SetTimer(this, n"Think", 3.0, bLooping = true);
	}

	UFUNCTION()
	void Think()
	{
        Print("AI is thinking");
		ATestActor Pawn = Cast<ATestActor>(GetControlledPawn());
		Pawn.Jump();
	}
}