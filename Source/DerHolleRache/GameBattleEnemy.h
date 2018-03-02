// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "GameEnemy.h"
#include "GameBattleEnemy.generated.h"

//============================================================================
// * UGameBattleEnemy
//----------------------------------------------------------------------------
// Extends UGameBattleEnemy for usage in battle, so that duplicate enemies
// can be a thing.
//============================================================================
UCLASS(Blueprintable)
class DERHOLLERACHE_API UGameBattleEnemy : public UGameEnemy {

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameBattleEnemy();
	~UGameBattleEnemy();
	virtual void setup(int id);
	void create(int id, int index);
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual int GetStatPlus(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetIndex();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual bool IsHero();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual bool IsEnemy();
	UFUNCTION(BlueprintPure, Category = "Battler")
		FName GetDisplayLetter();

	//------------------------------------------------------------------------
	// * Public Instance Variable Declaration
	//------------------------------------------------------------------------
	UPROPERTY(BlueprintReadWrite, Category = "Battler")
		bool DisplayIndex;

protected:
	//------------------------------------------------------------------------
	// * Protected Instance Variable Declaration
	//------------------------------------------------------------------------
	int index;

	//------------------------------------------------------------------------
	// * Constant Declaration
	//------------------------------------------------------------------------
	const static FName LetterTable[5];

	GENERATED_BODY()
};
