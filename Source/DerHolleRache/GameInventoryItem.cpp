//============================================================================
// * UGameInventoryItem
//----------------------------------------------------------------------------
// This class serves as a storage container for items, weapons, shields and 
// armor in the player's inventory.
//============================================================================
#include "GameInventoryItem.h"

//----------------------------------------------------------------------------
// * Object Initialization
//----------------------------------------------------------------------------
UGameInventoryItem::UGameInventoryItem() {

}

//----------------------------------------------------------------------------
// * Object Destruction
//----------------------------------------------------------------------------
UGameInventoryItem::~UGameInventoryItem() {

}

//----------------------------------------------------------------------------
// * Setup
//----------------------------------------------------------------------------
void UGameInventoryItem::setup(int id, char type) {
	this->id = id;
	this->type = type;
	Quantity = 1;
}

//----------------------------------------------------------------------------
// * Get ID
//----------------------------------------------------------------------------
int UGameInventoryItem::GetID() {
	return id;
}

//----------------------------------------------------------------------------
// * Match the Type
//----------------------------------------------------------------------------
bool UGameInventoryItem::typeMatch(char type) {
	return this->type == type;
}

//----------------------------------------------------------------------------
// * Get Type
//----------------------------------------------------------------------------
FName UGameInventoryItem::GetType() {
	char type[] = { getType() };
	return FName(type);
}

char UGameInventoryItem::getType() {
	return type;
}


//----------------------------------------------------------------------------
// * Get Name
//----------------------------------------------------------------------------
FName UGameInventoryItem::GetName() {
	switch (type) {
	case 'I':
		return getItemData().name;
	case 'W':
		return getWeaponData().name;
	case 'S':
		return getShieldData().name;
	case 'A':
	default:
		return getArmorData().name;
	}
}

//----------------------------------------------------------------------------
// * Get Description
//----------------------------------------------------------------------------
FText UGameInventoryItem::GetDescription() {
	switch (type) {
	case 'I':
		return getItemData().description;
	case 'W':
		return getWeaponData().description;
	case 'S':
		return getShieldData().description;
	case 'A':
	default:
		return getArmorData().description;
	}
}

//----------------------------------------------------------------------------
// * Check if Item is Consumable?
//----------------------------------------------------------------------------
bool UGameInventoryItem::IsConsumable() {
	switch (type) {
	case 'I':
		return getItemData().consumable;
	default:
		return false;
	}
}

//----------------------------------------------------------------------------
// * Check if Usable in the Field
//----------------------------------------------------------------------------
bool UGameInventoryItem::UsableInField() {
	switch (type) {
	case 'I':
		return getItemData().fieldUsable;
	default:
		return false;
	}
}

//----------------------------------------------------------------------------
// * Check if Usable in Battle
//----------------------------------------------------------------------------
bool UGameInventoryItem::UsableInBattle() {
	switch (type) {
	case 'I':
		return getItemData().battleUsable;
	default:
		return false;
	}
}

//----------------------------------------------------------------------------
// * Check if Key Item
//----------------------------------------------------------------------------
bool UGameInventoryItem::IsKeyItem() {
	switch (type) {
	case 'I':
		return getItemData().isKey;
	default:
		return false;
	}
}

//----------------------------------------------------------------------------
// * Parse Inventory Pocket
//----------------------------------------------------------------------------
int UGameInventoryItem::InventoryPocket() {
	switch (type) {
	case 'I':
		return getItemData().pocket;
	case 'W':
		return getWeaponData().pocket;
	case 'S':
		return getShieldData().pocket;
	case 'A':
	default:
		return getArmorData().pocket;
	}
}

//----------------------------------------------------------------------------
// * Get Item Data
//----------------------------------------------------------------------------
FData_Item &UGameInventoryItem::getItemData() {
	// Removed
	return gameInstance->DataItems[id - 1];
}

//----------------------------------------------------------------------------
// * Get Weapon Data
//----------------------------------------------------------------------------
FData_Weapon &UGameInventoryItem::getWeaponData() {
	// Removed
	return gameInstance->DataWeapons[id - 1];
}

//----------------------------------------------------------------------------
// * Get Shield Data
//----------------------------------------------------------------------------
FData_Shield &UGameInventoryItem::getShieldData() {
	// Removed
	return gameInstance->DataShields[id - 1];
}

//----------------------------------------------------------------------------
// * Get Armor Data
//----------------------------------------------------------------------------
FData_Armor &UGameInventoryItem::getArmorData() {
	// Removed
	return gameInstance->DataArmors[id - 1];
}

//----------------------------------------------------------------------------
// * Get Sorting Number
//----------------------------------------------------------------------------
int UGameInventoryItem::sortNum() {
	// Removed
	int ret = id;
	switch (type) {
	case 'A':
		ret += gameInstance->DataArmors.Num();
	case 'S':
		ret += gameInstance->DataShields.Num();
	case 'W':
		ret += gameInstance->DataWeapons.Num();
	}
	return ret;
}