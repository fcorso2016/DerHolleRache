//============================================================================
// * USystemControl
//----------------------------------------------------------------------------
// Static class that manages elements that are kept constant across maps.
//============================================================================
#include "SystemControl.h"
#include <string>

//----------------------------------------------------------------------------
// * Setup Class Variables
//----------------------------------------------------------------------------
int USystemControl::lastMenuIndex;
int USystemControl::lastItemPocket;
int USystemControl::lastHeroSelected;

//----------------------------------------------------------------------------
// * Setup Constants
//----------------------------------------------------------------------------
const int USystemControl::MaxItems = 99;

//----------------------------------------------------------------------------
// * Setup a New Save File
//----------------------------------------------------------------------------
void USystemControl::StartNewGame(USubGameInstance*  GameInstance) {
	setupAbilities(GameInstance);
	setupItems(GameInstance);
	setupStatuses(GameInstance);
	lastMenuIndex = 0;
	lastItemPocket = 0;
	lastHeroSelected = 0;
}

//----------------------------------------------------------------------------
// * Initialize the Abilities
//----------------------------------------------------------------------------
void USystemControl::setupAbilities(USubGameInstance*  gameInstance) {
	gameInstance->Abilities.Empty();
	for (int i = 0; i < gameInstance->DataAbilities.Num(); i++) {
		UGameAbility *abil = NewObject<UGameAbility>();
		abil->gameInstance = gameInstance;
		abil->setID(gameInstance->DataAbilities[i].id);
		abil->AddToRoot();
		gameInstance->Abilities.Add(abil);
	}
}

//----------------------------------------------------------------------------
// * Return the Ability Based on the Input ID
//----------------------------------------------------------------------------
UGameAbility *USystemControl::GetAbility(int id, USubGameInstance*  gameInstance) {
	return gameInstance->Abilities[id - 1];
}

//----------------------------------------------------------------------------
// * Return All the Abilities
//----------------------------------------------------------------------------
TArray<UGameAbility*> &USystemControl::GetAllAbilities(USubGameInstance*  gameInstance) {
	return gameInstance->Abilities;
}

//----------------------------------------------------------------------------
// * Initialize the Items
//----------------------------------------------------------------------------
void USystemControl::setupItems(USubGameInstance*  gameInstance) {
	gameInstance->Items.Empty();
	for (int i = 0; i < gameInstance->DataItems.Num(); i++) {
		UGameItem *item = NewObject<UGameItem>();
		item->gameInstance = gameInstance;
		item->setID(gameInstance->DataItems[i].id);
		item->AddToRoot();
		gameInstance->Items.Add(item);
	}
}

//----------------------------------------------------------------------------
// * Return the Item Based on the Input ID
//----------------------------------------------------------------------------
UGameItem *USystemControl::GetItem(int id, USubGameInstance*  gameInstance) {
	return gameInstance->Items[id - 1];
}

//----------------------------------------------------------------------------
// * Return All the Items
//----------------------------------------------------------------------------
TArray<UGameItem*> &USystemControl::GetAllItems(USubGameInstance*  gameInstance) {
	return gameInstance->Items;
}

//----------------------------------------------------------------------------
// * Initialize the Status Conditions
//----------------------------------------------------------------------------
void USystemControl::setupStatuses(USubGameInstance*  gameInstance) {
	for (int i = 0; i < gameInstance->Statuses.Num(); i++) {
		delete gameInstance->Statuses[i];
	}
	gameInstance->Statuses.Empty();
	for (int i = 0; i < gameInstance->DataStatuses.Num(); i++) {
		UGameStatus *status = NewObject<UGameStatus>();
		status->gameInstance = gameInstance;
		status->setID(gameInstance->DataStatuses[i].id);
		status->AddToRoot();
		gameInstance->Statuses.Add(status);
	}
}

//----------------------------------------------------------------------------
// * Return the Status Condition Based on the Input ID
//----------------------------------------------------------------------------
UGameStatus *USystemControl::GetStatus(int id, USubGameInstance*  gameInstance) {
	return gameInstance->Statuses[id - 1];
}

//----------------------------------------------------------------------------
// * Return All the Status Conditions
//----------------------------------------------------------------------------
TArray<UGameStatus*> &USystemControl::GetAllStatuses(USubGameInstance*  gameInstance) {
	return gameInstance->Statuses;
}

//----------------------------------------------------------------------------
// * Get the Current Menu Index
//----------------------------------------------------------------------------
int USystemControl::GetCurrentMenuIndex(USubGameInstance*  gameInstance) {
	return lastMenuIndex;
}

//----------------------------------------------------------------------------
// * Set the Current Menu Index
//----------------------------------------------------------------------------
int USystemControl::SetCurrentMenuIndex(int index, USubGameInstance*  gameInstance) {
	return lastMenuIndex = index;
}

//----------------------------------------------------------------------------
// * Get the Current Item Pocket
//----------------------------------------------------------------------------
int USystemControl::GetCurrentItemPocket(USubGameInstance*  gameInstance) {
	return lastItemPocket;
}

//----------------------------------------------------------------------------
// * Set the Current Item Pocket
//----------------------------------------------------------------------------
int USystemControl::SetCurrentItemPocket(int index, USubGameInstance*  gameInstance) {
	return lastItemPocket = index;
}

//----------------------------------------------------------------------------
// * Get the Current Party Member
//----------------------------------------------------------------------------
int USystemControl::GetCurrentPartyMember(USubGameInstance*  gameInstance) {
	return lastHeroSelected;
}

//----------------------------------------------------------------------------
// * Set the Current Party Member
//----------------------------------------------------------------------------
int USystemControl::SetCurrentPartyMember(int index, USubGameInstance*  gameInstance) {
	return lastHeroSelected = index;
}

//----------------------------------------------------------------------------
// * Get Inventory Item
//----------------------------------------------------------------------------
UGameInventoryItem *USystemControl::GetInventoryItem(int index, USubGameInstance*  gameInstance) {
	return gameInstance->Inventory[index];
}

//----------------------------------------------------------------------------
// * Get All Party Members
//----------------------------------------------------------------------------
TArray<UGameInventoryItem*> &USystemControl::GetPartyInventory(USubGameInstance*  gameInstance) {
	return gameInstance->Inventory;
}

//----------------------------------------------------------------------------
// * Find Item in Inventory
//----------------------------------------------------------------------------
UGameInventoryItem *USystemControl::FindItem(FString type, int id, USubGameInstance*  gameInstance) {
	std::string trueType(TCHAR_TO_UTF8(*type));
	return FindItem(trueType[0], id, gameInstance);
}

UGameInventoryItem *USystemControl::FindItem(char type, int id, USubGameInstance*  gameInstance) {
	for (int i = 0; i < gameInstance->Inventory.Num(); i++) {
		UGameInventoryItem *item = gameInstance->Inventory[i];
		if (item->typeMatch(type) && item->GetID() == id) {
			return item;
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------
// * Confirm if Item is in Inventory
//----------------------------------------------------------------------------
bool USystemControl::HasItem(FString type, int id, USubGameInstance*  gameInstance) {
	std::string trueType(TCHAR_TO_UTF8(*type));
	return HasItem(trueType[0], id, gameInstance);
}

bool USystemControl::HasItem(char type, int id, USubGameInstance*  gameInstance) {
	for (int i = 0; i < gameInstance->Inventory.Num(); i++) {
		UGameInventoryItem *item = gameInstance->Inventory[i];
		if (item->typeMatch(type) && item->GetID() == id) {
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------------
// * Get Item
//----------------------------------------------------------------------------
void USystemControl::GainItem(FString type, int id, int quantity, USubGameInstance*  gameInstance) {
	std::string trueType(TCHAR_TO_UTF8(*type));
	GainItem(trueType[0], id, quantity, gameInstance);
}

void USystemControl::GainItem(char type, int id, int quantity, USubGameInstance*  gameInstance) {
	if (HasItem(type, id, gameInstance)) {
		UGameInventoryItem *item = FindItem(type, id, gameInstance);
		item->Quantity += quantity;
		if (item->Quantity > MaxItems) {
			item->Quantity = MaxItems;
		} else if (item->Quantity <= 0) {
			gameInstance->Inventory.Remove(item);
			delete item;
		}
	} else {
		UGameInventoryItem *item = NewObject<UGameInventoryItem>();
		item->gameInstance = gameInstance;
		item->setup(id, type);
		item->Quantity = quantity;
		item->AddToRoot();
		gameInstance->Inventory.Add(item);
	}
}

//----------------------------------------------------------------------------
// * Lose Item
//----------------------------------------------------------------------------
void USystemControl::LoseItem(FString type, int id, int quantity, USubGameInstance*  gameInstance) {
	std::string trueType(TCHAR_TO_UTF8(*type));
	LoseItem(trueType[0], id, quantity, gameInstance);
}

void USystemControl::LoseItem(char type, int id, int quantity, USubGameInstance*  gameInstance) {
	GainItem(type, id, -quantity, gameInstance);
}

//----------------------------------------------------------------------------
// * Sort Items
//----------------------------------------------------------------------------
void USystemControl::SortItems(USubGameInstance*  gameInstance) {
	gameInstance->Inventory.Sort([](UGameInventoryItem &A, UGameInventoryItem &B) {
		return A.sortNum() < B.sortNum();
	});
}