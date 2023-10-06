// Copyright(C)2023 Valerio Santinelli


#include "GridGen.h"

#include "GameGrid.h"
#include "LD54AS/Actors/CratePawn.h"
#include "LD54AS/Actors/HeroPawn.h"
#include "LD54AS/Actors/TargetActor.h"
#include "LD54AS/Actors/WallPawn.h"


// Sets default values
AGridGen2::AGridGen2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGridGen2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridGen2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

    void AGridGen2::Initialize()
    {
        FString s = R"(
1111111111
1000000001
1020030101
1000040101
1000000101
1000000001
1111111111
)";
        AllGrids.Add(s);

        s = R"(
1111111111
1000000001
1020030101
1000000101
1000111101
1000040001
1111111111
)";
        AllGrids.Add(s);

        s = R"(
1111111111
1200001001
1000301001
1001111041
1000000001
1000000001
1111111111
)";
        AllGrids.Add(s);

        s = R"(
1111111111
1111111111
1111101111
1110111411
1030002011
1000410011
1001111111
1031111111
1001111111
1111111111
)";
        AllGrids.Add(s);

        s = R"(
1111111111
1111111111
1111110011
1111103011
1111104301
1110400001
1110111111
1112111111
1111111111
1111111111
)";
        AllGrids.Add(s);

        s = R"(
1111111111
1111100111
1111103111
1111100411
1112101111
1110004111
1110131111
1110001111
1111111111
1111111111
)";
        AllGrids.Add(s);

        s = R"(
1111111111
1111111111
1111400111
1114000111
1111100111
1111200001
1000030301
1031400111
1100001111
1111111111
)";
        AllGrids.Add(s);

        s = R"(
1111111111
1110000111
1100413111
1100110011
1110110111
1140300411
1112001111
1113011111
1110011111
1111111111
)";
        AllGrids.Add(s);
        s = R"(
1111111111
1111111111
1111140211
1111131111
1111400111
1030000111
1000000301
1111400001
1111111111
1111111111
)";
        AllGrids.Add(s);
        s = R"(
111111111111111
111111111111111
111111011111111
111111111002111
111111111311111
110041001011411
110011111001011
111011140041011
111011111101011
111011111101011
111011111101011
103300000001011
100000000001311
111111111100011
111111111111111
)";
        AllGrids.Add(s);
        s = R"(
111111111111
111111111111
111114000111
111111140111
110300001111
110004100011
111001101311
111003001011
112403430001
111100040301
111100111111
111111111111
)";
        AllGrids.Add(s);

    }

    FString AGridGen2::GridFromNumber(int GridNumber) {
        if (AllGrids.Num() > GridNumber-1) {
            return AllGrids[GridNumber-1];
        }
        return "";
    }

    int AGridGen2::NumLevels()
    {
        return AllGrids.Num();
    }

    void AGridGen2::GenerateLevel(FGrid2 G) {
        UClass *ActorToSpawn;
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
                	FVector Location = FVector(i * -100, j * 100, 250) + Offset;
                    AActor *Spawned = GetWorld()->SpawnActor(ActorToSpawn, &Location);
                    if (Spawned == nullptr) {
                        UE_LOG(LogTemp, Error, TEXT("no spawn"));
                    }
                }
            }
        }
    }