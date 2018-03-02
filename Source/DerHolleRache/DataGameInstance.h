#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DataGameInstance.generated.h"

//============================================================================
// * Data_Object
//----------------------------------------------------------------------------
// Base implementation for all RPG Data Objects.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Object {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FName name;
};

//============================================================================
// * Data_Battler
//----------------------------------------------------------------------------
// Superclass for Data_Hero and Data_Enemy.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Battler : public FData_Object {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FName sprite;
};

//============================================================================
// * Data_Hero
//----------------------------------------------------------------------------
// Sets the base parameters for a party member.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Hero : public FData_Battler {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int initialLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int maxLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int classId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> equips;

};

//============================================================================
// * Learning
//----------------------------------------------------------------------------
// Data class for classes.
//============================================================================
USTRUCT(BlueprintType)
struct FLearning {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int abilityId;
};

//============================================================================
// * Data_Class
//----------------------------------------------------------------------------
// Data class for classes.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Class : public FData_Object {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> baseStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<float> statIncreases;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> usableWeaponTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> usableShieldTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> usableArmorTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FLearning> learnings;
};

//============================================================================
// * Item_Drop
//----------------------------------------------------------------------------
// Cotains data for items dropped by enemies.
//============================================================================
USTRUCT(BlueprintType)
struct FItem_Drop {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int dropType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int itemId;
};

//============================================================================
// * Battle_Actions
//----------------------------------------------------------------------------
// Cotains data for actions taken by enemies.
//============================================================================
USTRUCT(BlueprintType)
struct FBattle_Action {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int itemId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int quantity; // Items only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int weight;
};

//============================================================================
// * Data_Enemy
//----------------------------------------------------------------------------
// Sets the base parameters for an enemy.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Enemy : public FData_Battler {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FItem_Drop> drops;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FBattle_Action> actions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> weaknesses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> resistances;

};

//============================================================================
// * Data_Action
//----------------------------------------------------------------------------
// Superclass for Data_Ability and Data_Item.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Action : public FData_Object {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int functionCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> elements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float accuracy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool battleUsable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool fieldUsable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FText description;

};

//============================================================================
// * Data_Ability
//----------------------------------------------------------------------------
// Handles all learnable abilities for the player.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Ability : public FData_Action {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int mpCost;
};

//============================================================================
// * Data_Item
//----------------------------------------------------------------------------
// Handles all usable items for the player.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Item : public FData_Action {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int pocket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool consumable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool isKey;
};

//============================================================================
// * Data_Equip
//----------------------------------------------------------------------------
// Superclass for Data_Weapon, Data_Shield and Data_Armor
//============================================================================
USTRUCT(BlueprintType)
struct FData_Equip : public FData_Object {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<int> stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int pocket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FText description;
};

//============================================================================
// * Data_Weapon
//----------------------------------------------------------------------------
// Data class for weapons.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Weapon : public FData_Equip {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float accuracy;
};

//============================================================================
// * Data_Shield
//----------------------------------------------------------------------------
// Data class for shields.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Shield : public FData_Equip {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float blockRate;
};

//============================================================================
// * Data_Armor
//----------------------------------------------------------------------------
// Data class for armor.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Armor : public FData_Equip {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int equipType;
};

//============================================================================
// * Data_Status
//----------------------------------------------------------------------------
// This is the data class for all status conditions.
//============================================================================
USTRUCT(BlueprintType)
struct FData_Status : public FData_Object {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int functionCode;
};

/**
 * 
 */
UCLASS()
class DERHOLLERACHE_API UDataGameInstance : public UGameInstance {
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Hero> DataHeros;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Enemy> DataEnemies;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Class> DataClasses;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Ability> DataAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Item> DataItems;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Weapon> DataWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Shield> DataShields;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Armor> DataArmors;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<struct FData_Status> DataStatuses;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<FName> Stats;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<FName> Elements;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<FName> EquipSlots;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<FName> WeaponTypes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<FName> ShieldTypes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<FName> ArmorTypes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")
		TArray<FName> Pockets;
	
};
