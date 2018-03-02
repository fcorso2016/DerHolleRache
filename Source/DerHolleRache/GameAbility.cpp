//============================================================================
// * UGameAbility
//----------------------------------------------------------------------------
// Extends UGameAction for the purpose of abilities.
//============================================================================
#include "GameAbility.h"

//----------------------------------------------------------------------------
// * Object Initialization
//----------------------------------------------------------------------------
UGameAbility::UGameAbility() {

}
 
//----------------------------------------------------------------------------
// * Object Destruction
//----------------------------------------------------------------------------
UGameAbility::~UGameAbility() {

}

//----------------------------------------------------------------------------
// * Get MP Cost
//----------------------------------------------------------------------------
int UGameAbility::GetMPCost() {
	return getAbilityData().mpCost;
}

//----------------------------------------------------------------------------
// * Get Action Data
//----------------------------------------------------------------------------
FData_Action UGameAbility::getActionData() {
	return getAbilityData();
}

//----------------------------------------------------------------------------
// * Get Ability Data
//----------------------------------------------------------------------------
FData_Ability UGameAbility::getAbilityData() {
	// Removed
	return gameInstance->DataAbilities[id - 1];
}

//----------------------------------------------------------------------------
// * Is this an Ability?
//----------------------------------------------------------------------------
bool UGameAbility::IsAbility() {
	return true;
}

//----------------------------------------------------------------------------
// * Is this an Item?
//----------------------------------------------------------------------------
bool UGameAbility::IsItem() {
	return false;
}