#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataControl.h"
#include "GameInventoryItem.generated.h"

//============================================================================
// * UGameInventoryItem
//----------------------------------------------------------------------------
// This class serves as a storage container for items, weapons, shields and 
// armor in the player's inventory.
//============================================================================
UCLASS(Blueprintable)
class DERHOLLERACHE_API UGameInventoryItem : public UObject {

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameInventoryItem();
	~UGameInventoryItem();
	void setup(int id, char type);
	UFUNCTION(BlueprintPure, Category = "Inventory")
		int GetID();
	bool typeMatch(char type);
	UFUNCTION(BlueprintPure, Category = "Inventory")
		FName GetType();
	char getType();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		FName GetName();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		FText GetDescription();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool IsConsumable();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool UsableInField();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool UsableInBattle();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool IsKeyItem();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		int InventoryPocket();
	int sortNum();

	//------------------------------------------------------------------------
	// * Public Instance Variable Declaration
	//------------------------------------------------------------------------
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
		int Quantity;
	UPROPERTY()
		UDataGameInstance* gameInstance;

protected:
	//------------------------------------------------------------------------
	// * Protected Method Declaration
	//------------------------------------------------------------------------
	FData_Item &getItemData();
	FData_Weapon &getWeaponData();
	FData_Shield &getShieldData();
	FData_Armor &getArmorData();

	//------------------------------------------------------------------------
	// * Protected Instance Variable Declaration
	//------------------------------------------------------------------------
	int id;
	char type;

	GENERATED_BODY()
};
