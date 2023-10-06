// Copyright(C)2023 Valerio Santinelli


#include "GameGrid.h"

FGrid2 UGameGrid2::ParseLevel(FString Str) {
	TArray<FString> Lines;
	FString Line;
	FString Leftover = Str;
	while (Leftover.Split("\n", &Line, &Leftover)) {
		Line = Line.TrimStartAndEnd();
		if (Line.Len() == 0) {
			continue;
		}
		Lines.Add(Line);
	}

	FGrid2 Level;
	Level.Width = Lines[0].Len();
	Level.Height = Lines.Num();
	for (int i = 0 ; i < Lines.Num() ; i++) {
		FString L = Lines[i];
		for (int j = 0 ; j < L.Len() ; j++) {
			Level.Grid.Add(L[j]);
		}
	}
	return Level;
}

int UGameGrid2::NumLevels()
{
	return 3;
}
