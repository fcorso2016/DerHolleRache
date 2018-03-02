// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameBattleEnemy.h"
#include "IntermediateGameInstance.h"
#include "GameInstance_SP.generated.h"

//============================================================================
// * UGameInstance_SP
//----------------------------------------------------------------------------
// Game Instance object that keeps a copy of all data members in order to
// protect them from garbage collection.
//============================================================================
UCLASS()
class DERHOLLERACHE_API UGameInstance_SP : public UIntermediateGameInstance {
	GENERATED_BODY()
	
public:

	//------------------------------------------------------------------------
	// * Public Instance Variable Declaration
	//------------------------------------------------------------------------
	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		TArray<UGameEnemy*> Enemies;
	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		TArray<UGameBattleEnemy*> EnemyTroop;

	UPROPERTY(BlueprintReadOnly, Category = "Data Protection")
		UGameInstance_SP *MemoryAddress;

	UFUNCTION(BlueprintCallable, Category = "Data Protection")
		void StoreSelf();
	
	
};
