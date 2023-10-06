// Copyright(C)2023 Valerio Santinelli


#include "JamPlayerState.h"

FText AJamPlayerState::GetPlayerDisplayName()
{
	return PlayerDisplayName;
}

void AJamPlayerState::SetPlayerDisplayName(FText Name)
{
	PlayerDisplayName = Name;
}
