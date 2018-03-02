// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubGameInstance.h"
#include "GameHero.h"
#include "IntermediateGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DERHOLLERACHE_API UIntermediateGameInstance : public USubGameInstance {
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		TArray<UGameHero*> Heros;
	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		TArray<UGameHero*> Party;
	
	
};
