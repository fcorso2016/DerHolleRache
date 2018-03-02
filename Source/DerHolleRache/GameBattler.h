#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStatus.h"
#include "SystemControl.h"
#include "GameBattler.generated.h"

//============================================================================
// * UGameBattler
//----------------------------------------------------------------------------
// Creates many of the base functionality for battlers as they function in
// battle. This class serves as the superclass for UGameHero and UGameEnemy.
//============================================================================
UCLASS(Blueprintable)
class DERHOLLERACHE_API UGameBattler : public UObject {
	
public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameBattler();
	~UGameBattler();
	virtual void setup(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetID();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetStatBase(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual int GetStatPlus(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetStat(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetCurrentHP();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetMaxHP();
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void ChangeHP(int newHp);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetCurrentMP();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetMaxMP();
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void ChangeMP(int newMp);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetAttack();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetDefense();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetMagic();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetResistance();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetSpeed();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetLuck();
	UFUNCTION(BlueprintPure, Category = "Battler")
		TArray<UGameStatus*> GetStatusConditions();
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void TakeDamage(int amt);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void Heal(int amt);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void TakeMPDamage(int amt);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void HealMP(int amt);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void AddStatus(int id);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void RemoveStatus(int id);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void ClearStatusConditions();
	UFUNCTION(BlueprintPure, Category = "Battler")
		bool IsDead();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual bool IsHero();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual bool IsEnemy();
	UFUNCTION(BlueprintPure, Category = "Battler")
		bool CheckCrit(UGameAction *action);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		virtual void PayCost(FString type, int id);
	virtual void PayCost(char type, int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual float GetAccuracy();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual float GetBlockRate();
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void BeginGuarding();
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void EndGuarding();
	UFUNCTION(BlueprintPure, Category = "Battler")
		bool IsGuarding();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual float ElementRate(int id);

	//------------------------------------------------------------------------
	// * Public Instance Variable Declaration
	//------------------------------------------------------------------------
	UPROPERTY(BlueprintReadWrite, Category = "Battler")
		FName Name;
	UPROPERTY(BlueprintReadWrite, Category = "Battler")
		int Level;
	UPROPERTY(BlueprintReadOnly, Category = "Battler")
		TArray<UGameStatus*> StatusConditions;
	UPROPERTY()
		USubGameInstance* gameInstance;

protected:
	//------------------------------------------------------------------------
	// * Protected Method Declaration
	//------------------------------------------------------------------------
	virtual void initBattler();
	void initHpAndMp();
	void die();

	//------------------------------------------------------------------------
	// * Protected Instance Variable Declaration
	//------------------------------------------------------------------------
	int id;
	int hp;
	int mp;
	int stats[8];
	int statPlus[8];
	bool guarding;

	GENERATED_BODY()
};
