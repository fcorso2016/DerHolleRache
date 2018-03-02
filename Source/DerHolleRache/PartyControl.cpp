//============================================================================
// * UPartyControl
//----------------------------------------------------------------------------
// Static class that manages the party and party related things.
//============================================================================
#include "PartyControl.h"
#include <string>

//----------------------------------------------------------------------------
// * Setup Constants
//----------------------------------------------------------------------------
const int UPartyControl::StartingParty[1] = { 1 }; // Start with the kid

//----------------------------------------------------------------------------
// * Setup a the Party and Heros
//----------------------------------------------------------------------------
void UPartyControl::InitHeros(UIntermediateGameInstance*  GameInstance) {
	setupHeros(GameInstance);
	setupParty(GameInstance);
}

//----------------------------------------------------------------------------
// * Prepare for Game Load
//----------------------------------------------------------------------------
void UPartyControl::PrepForLoad(UIntermediateGameInstance* gameInstance) {
	for (int i = 0; i < gameInstance->Heros.Num(); i++) {
		gameInstance->Heros[i]->Abilities.Empty();
		for (int j = 0; j < 5; j++) {
			gameInstance->Heros[i]->RemoveEquip(j, false);
		}
	}
	gameInstance->Party.Empty();
	gameInstance->Inventory.Empty();
}

//----------------------------------------------------------------------------
// * Initialize the Heros
//----------------------------------------------------------------------------
void UPartyControl::setupHeros(UIntermediateGameInstance* gameInstance) {
	// Removed
	gameInstance->Heros.Empty();
	for (int i = 0; i < gameInstance->DataHeros.Num(); i++) {
		UGameHero *hero = NewObject<UGameHero>();
		hero->gameInstance = gameInstance;
		hero->setup(gameInstance->DataHeros[i].id);
		hero->AddToRoot();
		gameInstance->Heros.Add(hero);
	}
}


//----------------------------------------------------------------------------
// * Initialize the Player's Party
//----------------------------------------------------------------------------
void UPartyControl::setupParty(UIntermediateGameInstance* gameInstance) {
	gameInstance->Party.Empty();
	for (int i = 0; i < 1; i++) {
		gameInstance->Party.Add(GetHero(StartingParty[i], gameInstance));
	}
	gameInstance->Inventory.Empty();
}

//----------------------------------------------------------------------------
// * Get Hero
//----------------------------------------------------------------------------
UGameHero *UPartyControl::GetHero(int id, UIntermediateGameInstance* gameInstance) {
	return gameInstance->Heros[id - 1];
}

//----------------------------------------------------------------------------
// * Get All Heros
//----------------------------------------------------------------------------
TArray<UGameHero*> &UPartyControl::GetAllHeros(UIntermediateGameInstance* gameInstance) {
	return gameInstance->Heros;
}

//----------------------------------------------------------------------------
// * Retrive Party Member
//----------------------------------------------------------------------------
UGameHero *UPartyControl::GetPartyMember(int index, UIntermediateGameInstance* gameInstance) {
	return gameInstance->Party[index];
}

//----------------------------------------------------------------------------
// * Retrive Party Leader
//----------------------------------------------------------------------------
UGameHero *UPartyControl::GetPartyLeader(UIntermediateGameInstance* gameInstance) {
	return GetPartyMember(0, gameInstance);
}

//----------------------------------------------------------------------------
// * Get All Party Members
//----------------------------------------------------------------------------
TArray<UGameHero*> &UPartyControl::GetAllPartyMembers(UIntermediateGameInstance* gameInstance) {
	return gameInstance->Party;
}

//----------------------------------------------------------------------------
// * All Dead
//----------------------------------------------------------------------------
bool UPartyControl::AllDead(UIntermediateGameInstance* gameInstance) {
	for (int i = 0; i < gameInstance->Party.Num(); i++) {
		if (!gameInstance->Party[i]->IsDead()) {
			return false;
		}
	}
	return true;
}

//----------------------------------------------------------------------------
// * Add Hero to the Party
//----------------------------------------------------------------------------
void UPartyControl::AddToParty(int id, UIntermediateGameInstance* gameInstance) {
	if (!CurrentlyInParty(id, gameInstance)) {
		gameInstance->Party.Add(gameInstance->Heros[id - 1]);
	}
}

//----------------------------------------------------------------------------
// * Remove Hero from the Party
//----------------------------------------------------------------------------
void UPartyControl::RemoveFromParty(int id, UIntermediateGameInstance* gameInstance) {
	for (int i = 0; gameInstance->Party.Num(); i++) {
		if (gameInstance->Party[i]->GetID() == id) {
			gameInstance->Party.RemoveAt(i);
			break;
		}
	}
}
//----------------------------------------------------------------------------
// * Check if Hero is In Party
//----------------------------------------------------------------------------
bool UPartyControl::CurrentlyInParty(int id, UIntermediateGameInstance* gameInstance) {
	for (int i = 0; i < gameInstance->Party.Num(); i++) {
		if (gameInstance->Party[i]->GetID() == id) {
			return true;
		}
	}
	return false;
}