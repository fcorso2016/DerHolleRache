//============================================================================
// * UGameBattleEnemy
//----------------------------------------------------------------------------
// Extends UGameBattleEnemy for usage in battle, so that duplicate enemies
// can be a thing.
//============================================================================
#include "GameBattleEnemy.h"

//----------------------------------------------------------------------------
// * Constants
//----------------------------------------------------------------------------
const FName UGameBattleEnemy::LetterTable[5] = { "A", "B", "C", "D", "E" };

//----------------------------------------------------------------------------
// * Object Initialization
//----------------------------------------------------------------------------
UGameBattleEnemy::UGameBattleEnemy() {
	index = 0;
	DisplayIndex = false;
}

//----------------------------------------------------------------------------
// * Object Destruction
//----------------------------------------------------------------------------
UGameBattleEnemy::~UGameBattleEnemy() {

}

//----------------------------------------------------------------------------
// * Setup
//----------------------------------------------------------------------------
void UGameBattleEnemy::setup(int id) {
	UGameEnemy::setup(id);
}

//----------------------------------------------------------------------------
// * Create
//----------------------------------------------------------------------------
void UGameBattleEnemy::create(int id, int index) {
	setup(id);
	this->index = index;
}

//----------------------------------------------------------------------------
// * Get Battle Index
//----------------------------------------------------------------------------
int UGameBattleEnemy::GetIndex() {
	return index;
}

//----------------------------------------------------------------------------
// * Get Stat Plus
//----------------------------------------------------------------------------
int UGameBattleEnemy::GetStatPlus(int id) {
	return UGameEnemy::GetStatPlus(id);
}

//----------------------------------------------------------------------------
// * Is Hero?
//----------------------------------------------------------------------------
bool UGameBattleEnemy::IsHero() {
	return false;
}

//----------------------------------------------------------------------------
// * Is Enemy?
//----------------------------------------------------------------------------
bool UGameBattleEnemy::IsEnemy() {
	return true;
}

//----------------------------------------------------------------------------
// * Get Display Letter
//----------------------------------------------------------------------------
FName UGameBattleEnemy::GetDisplayLetter() {
	return LetterTable[index];
}