// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JamPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class LD54AS_API AJamPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	FText PlayerDisplayName;

	UFUNCTION(BlueprintCallable, Category = "Player")
	FText GetPlayerDisplayName();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlayerDisplayName(FText Name);
};
