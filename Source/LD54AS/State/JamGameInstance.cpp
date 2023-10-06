// Copyright(C)2023 Valerio Santinelli


#include "JamGameInstance.h"

FText UJamGameInstance::GetPlayerDisplayName()
{
	return PlayerDisplayName;
}

void UJamGameInstance::SetPlayerDisplayName(FText PlayerName)
{
	PlayerDisplayName = PlayerName;
}
