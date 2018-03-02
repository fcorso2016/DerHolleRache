#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "GameBattler.h"
#include "GameEnemy.generated.h"

//============================================================================
// * UGameEnemy
//----------------------------------------------------------------------------
// Extends UGameBattler for usage by enemies.
//============================================================================
UCLASS()
class DERHOLLERACHE_API UGameEnemy : public UGameBattler {

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameEnemy();
	~UGameEnemy();
	virtual void setup(int id);
	void pickAction();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual int GetStatPlus(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual bool IsHero();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual bool IsEnemy();
	virtual void PayCost(char type, int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetExperienceYield(int gainerLevel);
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual float ElementRate(int id);

	//------------------------------------------------------------------------
	// * Public Instance Variable Declaration
	//------------------------------------------------------------------------
	FBattle_Action selectedAction;

protected:
	//------------------------------------------------------------------------
	// * Protected Method Declaration
	//------------------------------------------------------------------------
	virtual void initBattler();
	FData_Enemy getEnemyData();

	//------------------------------------------------------------------------
	// * Protected Instance Variable Declaration
	//------------------------------------------------------------------------
	TArray<FBattle_Action> actions;
	

	GENERATED_BODY()
};
