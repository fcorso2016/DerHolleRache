// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataGameInstance.h"
#include "GameAbility.h"
#include "GameItem.h"
#include "GameStatus.h"
#include "GameInventoryItem.h"
#include "SubGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DERHOLLERACHE_API USubGameInstance : public UDataGameInstance {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		TArray<UGameAbility*> Abilities;
	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		TArray<UGameItem*> Items;
	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		TArray<UGameStatus*> Statuses;
	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		TArray<UGameInventoryItem*> Inventory;
	
	
};
