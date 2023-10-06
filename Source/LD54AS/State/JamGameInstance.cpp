// Copyright(C)2023 Valerio Santinelli


#include "JamGameInstance.h"

FText UJamGameInstance2::GetPlayerDisplayName()
{
	return PlayerDisplayName;
}

void UJamGameInstance2::SetPlayerDisplayName(FText PlayerName)
{
	PlayerDisplayName = PlayerName;
}
