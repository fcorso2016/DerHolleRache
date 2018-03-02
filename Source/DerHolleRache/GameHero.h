#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "GameBattler.h"
#include "GameHero.generated.h"

//============================================================================
// * EquipComparison
//----------------------------------------------------------------------------
// Struct that stores the equips of all the equipment for optimization
// purposes.
//============================================================================
struct EquipComparison {
	int bestEquipment[4];
	int weaponAtk; // Weapons judge potential by attack
	float shieldBlk; // Shields judge potential by block rate
	int helmRes; // Helms judge potential by resistance
	int armorDef; // Armors judge potential by defense
};

//============================================================================
// * FHeroSaveData
//----------------------------------------------------------------------------
// Struct that saves hero save data in basic data types to avoid pointer
// destruction.
//============================================================================
USTRUCT(Blueprintable)
struct FHeroSaveData {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		int ID;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		FName Name;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		int ClassID;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		int Level;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		int CurrentHP;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		int CurrentMP;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		TArray<int> Stats;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		TArray<int> StatPlus;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		TArray<int> Equips;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		TArray<int> Abilities;
	UPROPERTY(BlueprintReadWrite, Category = "Saving")
		int EXP;
};

//============================================================================
// * FLevelUpInfo
//----------------------------------------------------------------------------
// Struct that stores data about a level up.
//============================================================================
USTRUCT(Blueprintable)
struct FLevelUpInfo {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, Category = "Batter")
		bool LeveledUp;
	UPROPERTY(BlueprintReadOnly, Category = "Batter")
		TArray<int> NewAbilities;
};

//============================================================================
// * UGameHero
//----------------------------------------------------------------------------
// Extends default battler functionality for the player.
//============================================================================
UCLASS(Blueprintable)
class DERHOLLERACHE_API UGameHero : public UGameBattler {

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameHero();
	~UGameHero();
	void setup(int id);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void SetupWithClass(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		FName GetClassName();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetClassID();
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void ChangeClass(int id);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		TArray<int> ChangeLevel(int NewLevel);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		TArray<int> LevelUp();
	UFUNCTION(BlueprintCallable, Category = "Battler")
		TArray<int> LevelDown();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetStatPlus(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetStatPlusBase(int id);
	UFUNCTION(BlueprintPure, Category = "Battler")
		FName GetEquipName(int index);
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual bool IsHero();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual bool IsEnemy();
	virtual void PayCost(char type, int id);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		FLevelUpInfo GainExperience(int exp);
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetCurrentExperience();
	UFUNCTION(BlueprintPure, Category = "Battler")
		int GetEquipID(int slot);
	UFUNCTION(BlueprintPure, Category = "Battler")
		bool CanEquip(FString type, int id);
	bool CanEquip(char type, int id);
	void ChangeEquip(int slot, int id, bool affectInventory = true);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void ChangeEquip(FString type, int id, bool affectInventory = true);
	void ChangeEquip(char type, int id, bool affectInventory = true);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void RemoveEquip(int slot, bool affectInventory = true);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void OptimizeEquipment(bool affectInventory = true);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void ClearEquipment(bool affectInventory = true);
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual float GetAccuracy();
	UFUNCTION(BlueprintPure, Category = "Battler")
		virtual float GetBlockRate();
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void SetStat(int id, int base, int plus);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void PrepForLoad();
	UFUNCTION(BlueprintPure, Category = "Battler")
		bool AbilityLearned(int id, bool loading = false);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void LearnAbility(int id, bool loading = false);
	UFUNCTION(BlueprintCallable, Category = "Battler")
		void ForgetAbility(int id, bool loading = false);

	
	UPROPERTY(BlueprintReadOnly, Category = "Battler")
		TArray<int> Abilities;

protected:
	//------------------------------------------------------------------------
	// * Protected Method Declaration
	//------------------------------------------------------------------------
	virtual void initBattler();
	FData_Hero getHeroData();
	FData_Class getClassData();
	void processLevelUp();

	//------------------------------------------------------------------------
	// * Protected Class Variable Declaration
	//------------------------------------------------------------------------
	static FName EmptyEquipName;

	//------------------------------------------------------------------------
	// * Protected Instance Variable Declaration
	//------------------------------------------------------------------------
	int classID;
	int equips[5];
	int exp;

private:
	GENERATED_BODY()
};
