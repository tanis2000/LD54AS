class AGridGen: AActor
{
    UPROPERTY()
    TSubclassOf<AWallPawn> Wall;

    UPROPERTY()
    TSubclassOf<AHeroPawn> Hero;

    UPROPERTY()
    TSubclassOf<ACratePawn> Crate;
    
    UPROPERTY()
    TSubclassOf<ATargetActor> Target;

    UPROPERTY()
    TArray<FString> AllGrids;

    void Initialize()
    {
        FString s = "
1111111111
1000000001
1020030101
1000040101
1000000101
1000000001
1111111111
";
        AllGrids.Add(s);

        s = "
1111111111
1000000001
1020030101
1000000101
1000111101
1000040001
1111111111
";
        AllGrids.Add(s);

        s = "
1111111111
1200000001
1000300001
1000000141
1000111101
1000000001
1111111111
";
        AllGrids.Add(s);
    }

    FString GridFromNumber(int GridNumber) {
        if (AllGrids.Num() > GridNumber-1) {
            return AllGrids[GridNumber-1];
        }
        return "";
    }

    int NumLevels()
    {
        return AllGrids.Num();
    }

    void GenerateLevel(FGrid G) {
        UClass ActorToSpawn;
        FVector Offset = FVector(-(G.Height * -100 / 2.0), -(G.Width * 100 / 2.0), 0); 
        for (int i = 0 ; i < G.Height ; i++) {
            for (int j = 0 ; j < G.Width ; j++) {
                int ActorType = G.Grid[i * G.Width + j];
                switch(ActorType) {
                    case '1':
                        ActorToSpawn = Wall.Get();
                        break;
                    case '2':
                        ActorToSpawn = Hero.Get();
                        break;
                    case '3':
                        ActorToSpawn = Crate.Get();
                        break;
                    case '4':
                        ActorToSpawn = Target.Get();
                        break;
                    default:
                        ActorToSpawn = nullptr;
                        break;
                }
                if (ActorToSpawn != nullptr) {
                    AActor Spawned = SpawnActor(ActorToSpawn, FVector(i * -100, j * 100, 250) + Offset);
                    if (Spawned == nullptr) {
                        PrintError("no spawn");
                    }
                }
            }
        }
    }
}