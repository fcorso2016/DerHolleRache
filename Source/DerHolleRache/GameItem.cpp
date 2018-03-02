//============================================================================
// * UGameItem
//----------------------------------------------------------------------------
// Extends UGameAction for the purpose of items.
//============================================================================
#include "GameItem.h"

//----------------------------------------------------------------------------
// * Object Initialization
//----------------------------------------------------------------------------
UGameItem::UGameItem() {

}

//----------------------------------------------------------------------------
// * Object Destruction
//----------------------------------------------------------------------------
UGameItem::~UGameItem() {

}

//----------------------------------------------------------------------------
// * Determine if the Item Should be Consumed
//----------------------------------------------------------------------------
bool UGameItem::IsConsumable() {
	return getItemData().consumable;
}

//----------------------------------------------------------------------------
// * Determine if the Item is Key Item
//----------------------------------------------------------------------------
bool UGameItem::IsKeyItem() {
	return getItemData().isKey;
}

//----------------------------------------------------------------------------
// * Get Pocket
//----------------------------------------------------------------------------
int UGameItem::GetPocket() {
	return getItemData().pocket;
}

//----------------------------------------------------------------------------
// * Get Action Data
//----------------------------------------------------------------------------
FData_Action UGameItem::getActionData() {
	return getItemData();
}

//----------------------------------------------------------------------------
// * Get Item Data
//----------------------------------------------------------------------------
FData_Item UGameItem::getItemData() {
	// Removed
	return gameInstance->DataItems[id - 1];
}

//----------------------------------------------------------------------------
// * Is this an Ability?
//----------------------------------------------------------------------------
bool UGameItem::IsAbility() {
	return false;
}

//----------------------------------------------------------------------------
// * Is this an Item?
//----------------------------------------------------------------------------
bool UGameItem::IsItem() {
	return true;
}