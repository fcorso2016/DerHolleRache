//============================================================================
// * UGameEnemy
//----------------------------------------------------------------------------
// Extends UGameBattler for usage by enemies.
//============================================================================
#include "GameEnemy.h"

//----------------------------------------------------------------------------
// * Object Initialization
//----------------------------------------------------------------------------
UGameEnemy::UGameEnemy() {
	selectedAction = { 0, 1, 0, 0 };
}

//----------------------------------------------------------------------------
// * Object Destruction
//----------------------------------------------------------------------------
UGameEnemy::~UGameEnemy() {

}

//----------------------------------------------------------------------------
// * Setup
//----------------------------------------------------------------------------
void UGameEnemy::setup(int id) {
	this->id = id;
	Name = getEnemyData().name;
	Level = getEnemyData().level;
	actions = getEnemyData().actions;
	if (actions.Num() > 0) {
		selectedAction = actions[0];
	}
	UGameBattler::setup(id);
}

//----------------------------------------------------------------------------
// * Init Basic Properties of the Battler
//----------------------------------------------------------------------------
void UGameEnemy::initBattler() {
	for (int i = 0; i < 8; i++) {
		stats[i] = getEnemyData().stats[i];
	}
}

//----------------------------------------------------------------------------
// * Get Stat Plus
//----------------------------------------------------------------------------
int UGameEnemy::GetStatPlus(int id) {
	return UGameBattler::GetStatPlus(id);
}

//----------------------------------------------------------------------------
// * Select an Action for Combat
//----------------------------------------------------------------------------
void UGameEnemy::pickAction() {
	int totalWeight = 0;
	TArray<int> weights;
	for (int i = 0; i < actions.Num(); i++) {
		totalWeight += actions[i].weight;
		weights.Add(totalWeight);
	}
	int randomNum = FMath::RandRange(0, totalWeight);
	for (int i = 0; i < weights.Num(); i++) {
		if (weights[i] < randomNum) {
			selectedAction = actions[i];
			break;
		}
	}
}

//----------------------------------------------------------------------------
// * Select an Action for Combat
//----------------------------------------------------------------------------
FData_Enemy UGameEnemy::getEnemyData() {
	// Removed
	return gameInstance->DataEnemies[id - 1];
}

//----------------------------------------------------------------------------
// * Is Hero?
//----------------------------------------------------------------------------
bool UGameEnemy::IsHero() {
	return false;
}

//----------------------------------------------------------------------------
// * Is Enemy?
//----------------------------------------------------------------------------
bool UGameEnemy::IsEnemy() {
	return true;
}

//----------------------------------------------------------------------------
// * Pay Action Cost
//----------------------------------------------------------------------------
void UGameEnemy::PayCost(char type, int id) {
	switch (type) {
	case 'I':
		for (int i = 0; i < actions.Num(); i++) {
			if (actions[i].type == 1 && actions[i].itemId == id && actions[i].quantity > 0) {
				actions[i].quantity--;
			}
		}
		break;
	default:
		UGameBattler::PayCost(type, id);
		break;
	}
}

//----------------------------------------------------------------------------
// * Get EXP Yield
//----------------------------------------------------------------------------
int UGameEnemy::GetExperienceYield(int gainerLevel) {
	return fmax(getEnemyData().exp + getEnemyData().level - gainerLevel, 1);
}

//----------------------------------------------------------------------------
// * Get EXP Yield
//----------------------------------------------------------------------------
float UGameEnemy::ElementRate(int id) {
	float ret = UGameBattler::ElementRate(id);
	if (getEnemyData().weaknesses.Find(id)) {
		ret *= 2;
	}
	if (getEnemyData().resistances.Find(id)) {
		ret /= 2;
	}
	return ret;
}