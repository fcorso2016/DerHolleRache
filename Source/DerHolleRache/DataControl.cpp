//============================================================================
// * UDataControl
//----------------------------------------------------------------------------
// Static class that creates all the data structures used by the game.
//============================================================================
#include "DataControl.h"
#include <string>

//----------------------------------------------------------------------------
// * Setup Class Variables
//----------------------------------------------------------------------------
UDataGameInstance* UDataControl::gameInstance;

//----------------------------------------------------------------------------
// * Get Stat
//----------------------------------------------------------------------------
FName UDataControl::GetStat(int id, UDataGameInstance* gameInstance) {
	// Removed
	return gameInstance->Stats[id];
}

//----------------------------------------------------------------------------
// * Get Element
//----------------------------------------------------------------------------
FName UDataControl::GetElement(int id, UDataGameInstance* gameInstance) {
	// Removed
	return gameInstance->Elements[id];
}

//----------------------------------------------------------------------------
// * Get Equip Slot
//----------------------------------------------------------------------------
FName UDataControl::GetEquipSlot(int index, UDataGameInstance* gameInstance) {
	// Removed
	return gameInstance->EquipSlots[index];
}

//----------------------------------------------------------------------------
// * Get Weapon Type
//----------------------------------------------------------------------------
FName UDataControl::GetWeaponType(int id, UDataGameInstance* gameInstance) {
	// Removed
	return gameInstance->WeaponTypes[id];
}

//----------------------------------------------------------------------------
// * Get Shield Type
//----------------------------------------------------------------------------
FName UDataControl::GetShieldType(int id, UDataGameInstance* gameInstance) {
	// Removed
	return gameInstance->ShieldTypes[id];
}

//----------------------------------------------------------------------------
// * Get Armor Type
//----------------------------------------------------------------------------
FName UDataControl::GetArmorType(int id, UDataGameInstance* gameInstance) {
	// Removed
	return gameInstance->ArmorTypes[id];
}

//----------------------------------------------------------------------------
// * Get Armor Type
//----------------------------------------------------------------------------
FName UDataControl::GetPocket(int id, UDataGameInstance* gameInstance) {
	// Removed
	return gameInstance->Pockets[id];
}

//----------------------------------------------------------------------------
// * Get Item Name
//----------------------------------------------------------------------------
FName UDataControl::GetItemName(FString type, int id, UDataGameInstance* gameInstance) {
	std::string trueType(TCHAR_TO_UTF8(*type));
	return GetItemName(trueType[0], id, gameInstance);
}

FName UDataControl::GetItemName(char type, int id, UDataGameInstance* gameInstance) {
	// Removed
	switch (type) {
	case 'I':
		return gameInstance->DataItems[id - 1].name;
	case 'W':
		return gameInstance->DataWeapons[id - 1].name;
	case 'S':
		return gameInstance->DataShields[id - 1].name;
	default:
		return gameInstance->DataArmors[id - 1].name;
	}
}