// Copyright(C)2023 Valerio Santinelli


#include "JamPlayerState.h"

FText AJamPlayerState2::GetPlayerDisplayName()
{
	return PlayerDisplayName;
}

void AJamPlayerState2::SetPlayerDisplayName(FText Name)
{
	PlayerDisplayName = Name;
}
