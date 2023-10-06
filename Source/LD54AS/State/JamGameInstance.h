// Copyright(C)2023 Valerio Santinelli

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LD54AS_API UJamGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FText PlayerDisplayName;

	UPROPERTY(BlueprintReadWrite)
	int CurrentLevel = 1;

	UFUNCTION(BlueprintCallable, Category = "Player")
	FText GetPlayerDisplayName();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlayerDisplayName(FText PlayerName);
};
