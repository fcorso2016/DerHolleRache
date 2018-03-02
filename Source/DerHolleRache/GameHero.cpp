//============================================================================
// * UGameHero
//----------------------------------------------------------------------------
// Extends default battler functionality for the player.
//============================================================================
#include "GameHero.h"
#include <string>

//----------------------------------------------------------------------------
// * Class Variables
//----------------------------------------------------------------------------
FName UGameHero::EmptyEquipName = FName(TEXT("<DEFAULT>"));

//----------------------------------------------------------------------------
// * Object Initialization
//----------------------------------------------------------------------------
UGameHero::UGameHero() {

}

//----------------------------------------------------------------------------
// * Object Destruction
//----------------------------------------------------------------------------
UGameHero::~UGameHero() {

}

//----------------------------------------------------------------------------
// * Setup
//----------------------------------------------------------------------------
void UGameHero::setup(int id) {
	this->id = id;
	Name = getHeroData().name;
	classID = getHeroData().classId;
	Level = getHeroData().initialLevel;
	exp = 0;
	UGameBattler::setup(id);
}

//----------------------------------------------------------------------------
// * Setup with Class
//----------------------------------------------------------------------------
void UGameHero::SetupWithClass(int id) {
	classID = id;
	Level = getHeroData().initialLevel;
	exp = 0;
	Abilities.Empty();
	UGameBattler::setup(this->id);
}

//----------------------------------------------------------------------------
// * Init Basic Properties of the Battler
//----------------------------------------------------------------------------
void UGameHero::initBattler() {
	for (int i = 0; i < 8; i++) {
		stats[i] = getClassData().baseStats[i];
	}
	for (int i = 0; i < 5; i++) {
		equips[i] = getHeroData().equips[i];
	}
	for (int i = 0; i < getClassData().learnings.Num(); i++) {
		FLearning learning = getClassData().learnings[i];
		if (Level >= learning.level) {
			Abilities.Add(learning.abilityId);
		}
	}
}

//----------------------------------------------------------------------------
// * Get Hero Data
//----------------------------------------------------------------------------
FData_Hero UGameHero::getHeroData() {
	// Removed
	return gameInstance->DataHeros[id - 1];
}

//----------------------------------------------------------------------------
// * Get Class Data
//----------------------------------------------------------------------------
FData_Class UGameHero::getClassData() {
	// Removed
	return gameInstance->DataClasses[classID - 1];
}

//----------------------------------------------------------------------------
// * Get Class Name
//----------------------------------------------------------------------------
FName UGameHero::GetClassName() {
	return getClassData().name;
}

//----------------------------------------------------------------------------
// * Get Class ID
//----------------------------------------------------------------------------
int UGameHero::GetClassID() {
	return classID;
}

//----------------------------------------------------------------------------
// * Change Class
//----------------------------------------------------------------------------
void UGameHero::ChangeClass(int id) {
	classID = id;
}

//----------------------------------------------------------------------------
// * Change Hero Level
//----------------------------------------------------------------------------
TArray<int> UGameHero::ChangeLevel(int NewLevel) {
	int lvl = fmax(1, fmin(NewLevel, getHeroData().maxLevel));
	TArray<int> newAbils;
	if (lvl > Level) {
		for (int i = 0; i < (lvl - Level); i++) {
			processLevelUp();
			for (int j = 0; j < getClassData().learnings.Num(); j++) {
				if (!AbilityLearned(id) && getClassData().learnings[j].level == Level + i) {
					LearnAbility(getClassData().learnings[j].abilityId);
					newAbils.Add(getClassData().learnings[j].abilityId);
				}
			}
		}
	}
	Level = lvl;
	return newAbils;
}

//----------------------------------------------------------------------------
// * Level Up
//----------------------------------------------------------------------------
TArray<int> UGameHero::LevelUp() {
	return ChangeLevel(Level + 1);
}

//----------------------------------------------------------------------------
// * Process Level Up
//----------------------------------------------------------------------------
void UGameHero::processLevelUp() {
	for (int i = 0; i < 8; i++) {
		if (FMath::RandRange(0.0f, 1.0f) < getClassData().statIncreases[i]) {
			if (i < 2) { 
				stats[i] += 2; // Increase HP and MP by 2
			} else {
				stats[i] += 1; // Increase all other stats by 1
			}
		}
	}
}

//----------------------------------------------------------------------------
// * Level Down
//----------------------------------------------------------------------------
TArray<int> UGameHero::LevelDown() {
	return ChangeLevel(Level - 1);
}

//----------------------------------------------------------------------------
// * Return a Stat for a Battler
//----------------------------------------------------------------------------
int UGameHero::GetStatPlus(int id) {
	// Removed
	int ret = UGameBattler::GetStatPlus(id);
	for (int i = 0; i < 5; i++) {
		int equipId = equips[i];
		if (equipId > 0) {
			switch (i) {
			case 0:
				ret += gameInstance->DataWeapons[equipId - 1].stats[id];
				break;
			case 1:
				ret += gameInstance->DataShields[equipId - 1].stats[id];
				break;
			default:
				ret += gameInstance->DataArmors[equipId - 1].stats[id];
				break;
			}
		}
	}
	return ret;
}

//----------------------------------------------------------------------------
// * Return a Stat for a Battler
//----------------------------------------------------------------------------
int UGameHero::GetStatPlusBase(int id) {
	return statPlus[id];
}

//----------------------------------------------------------------------------
// * Get Equip ID
//----------------------------------------------------------------------------
int UGameHero::GetEquipID(int slot) {
	return equips[slot];
}

//----------------------------------------------------------------------------
// * Get Equip
//----------------------------------------------------------------------------
FName UGameHero::GetEquipName(int index) {
	// Removed
	int id = equips[index];
	if (id > 0) {
		switch (index) {
		case 0:
			return gameInstance->DataWeapons[id - 1].name;
		case 1:
			return gameInstance->DataShields[id - 1].name;
		default:
			return gameInstance->DataArmors[id - 1].name;
		}
	}
	return EmptyEquipName;
}

//----------------------------------------------------------------------------
// * Is Hero?
//----------------------------------------------------------------------------
bool UGameHero::IsHero() {
	return true;
}

//----------------------------------------------------------------------------
// * Is Enemy?
//----------------------------------------------------------------------------
bool UGameHero::IsEnemy() {
	return false;
}

//----------------------------------------------------------------------------
// * Pay Action Cost
//----------------------------------------------------------------------------
void UGameHero::PayCost(char type, int id) {
	switch (type) {
	case 'I':
		USystemControl::LoseItem('I', id, 1, gameInstance);
		break;
	default:
		UGameBattler::PayCost(type, id);
		break;
	}
}

//----------------------------------------------------------------------------
// * Gain Exp
//----------------------------------------------------------------------------
FLevelUpInfo UGameHero::GainExperience(int exp) {
	FLevelUpInfo levelInfo;
	levelInfo.LeveledUp = false;
	levelInfo.NewAbilities.Empty();
	this->exp += exp;
	if (this->exp >= 100) {
		levelInfo.LeveledUp = true;
		int levels = this->exp / 100;
		for (int i = 0; i < levels; i++) {
			levelInfo.NewAbilities.Append(LevelUp());
			this->exp -= 100;
		}
	}
	return levelInfo;
}

//----------------------------------------------------------------------------
// * Get Current Exp
//----------------------------------------------------------------------------
int UGameHero::GetCurrentExperience() {
	return exp;
}

//----------------------------------------------------------------------------
// * Get If the Hero Can Equip a Certain Piece of Equipment
//----------------------------------------------------------------------------
bool UGameHero::CanEquip(FString type, int id) {
	std::string trueType(TCHAR_TO_UTF8(*type));
	return CanEquip(trueType[0], id);
}

bool UGameHero::CanEquip(char type, int id) {
	// Removed
	int equipType;
	switch (type) {
	case 'W':
		equipType = gameInstance->DataWeapons[id - 1].category;
		for (int i = 0; i < getClassData().usableWeaponTypes.Num(); i++) {
			if (getClassData().usableWeaponTypes[i] == equipType) {
				return true;
			}
		}
		return false;
	case 'S':
		equipType = gameInstance->DataShields[id - 1].category;
		for (int i = 0; i < getClassData().usableShieldTypes.Num(); i++) {
			if (getClassData().usableShieldTypes[i] == equipType) {
				return true;
			}
		}
		return false;
	case 'A':
		equipType = gameInstance->DataArmors[id - 1].category;
		for (int i = 0; i < getClassData().usableArmorTypes.Num(); i++) {
			if (getClassData().usableArmorTypes[i] == equipType) {
				return true;
			}
		}
		return false;
	default:
		return false;
	}
}

//----------------------------------------------------------------------------
// * Change Equip
//----------------------------------------------------------------------------
void UGameHero::ChangeEquip(int slot, int id, bool affectInventory) {
	if (id > 0) {
		if (affectInventory) {
			switch (slot) {
			case 0:
				USystemControl::LoseItem('W', id, 1, gameInstance);
				if (equips[slot] > 0) {
					USystemControl::GainItem('W', id, 1, gameInstance);
				}
				break;
			case 1:
				USystemControl::LoseItem('S', id, 1, gameInstance);
				if (equips[slot] > 0) {
					USystemControl::GainItem('S', id, 1, gameInstance);
				}
				break;
			default:
				USystemControl::LoseItem('A', id, 1, gameInstance);
				if (equips[slot] > 0) {
					USystemControl::GainItem('A', id, 1, gameInstance);
				}
				break;
			}
		}
	}
	equips[slot] = id;
}

void UGameHero::ChangeEquip(FString type, int id, bool affectInventory) {
	std::string trueType(TCHAR_TO_UTF8(*type));
	ChangeEquip(trueType[0], id, affectInventory);
}

void UGameHero::ChangeEquip(char type, int id, bool affectInventory) {
	// Removed
	if (id > 0) {
		USystemControl::LoseItem(type, id, 1, gameInstance);
		switch (type) {
		case 'W':
			if (equips[0] > 0) {
				USystemControl::GainItem(type, equips[0], 1, gameInstance);
			}
			equips[0] = id;
			break;
		case 'S':
			if (equips[1] > 0) {
				USystemControl::GainItem(type, equips[1], 1, gameInstance);
			}
			equips[1] = id;
			break;
		default:
			if (equips[gameInstance->DataArmors[id - 1].equipType] > 0) {
				USystemControl::GainItem(type, equips[gameInstance->DataArmors[id - 1].equipType], 1, gameInstance);
			}
			equips[gameInstance->DataArmors[id - 1].equipType] = id;
			break;
		}
	}
}

//----------------------------------------------------------------------------
// * Remove Equip
//----------------------------------------------------------------------------
void UGameHero::RemoveEquip(int slot, bool affectInventory) {
	if (affectInventory && equips[slot] > 0) {
		switch (slot) {
		case 0:
			USystemControl::GainItem('W', equips[slot], 1, gameInstance);
			break;
		case 1:
			USystemControl::GainItem('S', equips[slot], 1, gameInstance);
			break;
		default:
			USystemControl::GainItem('A', equips[slot], 1, gameInstance);
			break;
		}
	}
	equips[slot] = 0;
}

//----------------------------------------------------------------------------
// * Optimize Equipment
//----------------------------------------------------------------------------
void UGameHero::OptimizeEquipment(bool affectInventory) {
	// Removed
	// When optimizing don't change the accessory as it doesn't change stats.
	EquipComparison optim = { { 0, 0, 0, 0 },  0, 0.0f, 0, 0 };
	if (equips[0] > 0) {
		optim.weaponAtk = gameInstance->DataWeapons[equips[0] - 1].stats[2]; // Weapons judge potential by attack
	}
	if (equips[1] > 0) {
		optim.shieldBlk = gameInstance->DataShields[equips[1] - 1].blockRate; // Shields judge potential by block rate
	}
	if (equips[2] > 0) {
		optim.helmRes = gameInstance->DataArmors[equips[2] - 1].stats[5]; // Helms judge potential by resistance
	}
	if (equips[3] > 0) {
		optim.armorDef = gameInstance->DataArmors[equips[3] - 1].stats[3]; // Armors judge potential by defense
	}
	for (int i = 0; i < gameInstance->Inventory.Num(); i++) {
		UGameInventoryItem *item = gameInstance->Inventory[i];
		int itemID = item->GetID();
		int equipType;
		switch (item->getType()) {
		case 'W': 
			if (gameInstance->DataWeapons[itemID - 1].stats[2] > optim.weaponAtk) {
				optim.bestEquipment[0] = itemID;
				optim.weaponAtk = gameInstance->DataWeapons[itemID - 1].stats[2];
			}
			break;
		case 'S':
			if (gameInstance->DataShields[itemID - 1].blockRate > optim.shieldBlk) {
				optim.bestEquipment[1] = itemID;
				optim.shieldBlk = gameInstance->DataShields[itemID - 1].blockRate;
			}
			break;
		case 'A':
			equipType = gameInstance->DataArmors[itemID - 1].equipType;
			switch (equipType) {
			case 2:
				if (gameInstance->DataArmors[itemID - 1].stats[5] > optim.helmRes) {
					optim.bestEquipment[2] = itemID;
					optim.helmRes = gameInstance->DataArmors[itemID - 1].stats[5];
				}
				break;
			case 3:
				if (gameInstance->DataArmors[itemID - 1].stats[3] > optim.armorDef) {
					optim.bestEquipment[2] = itemID;
					optim.armorDef = gameInstance->DataArmors[itemID - 1].stats[3];
				}
				break;
			}
			
		}
	}
	for (int i = 0; i < 4; i++) {
		ChangeEquip(i, optim.bestEquipment[i], affectInventory);
	}
}

//----------------------------------------------------------------------------
// * Clear Equipment
//----------------------------------------------------------------------------
void UGameHero::ClearEquipment(bool affectInventory) {
	for (int i = 0; i < 5; i++) {
		RemoveEquip(i, affectInventory);
	}
}

//----------------------------------------------------------------------------
// * Get Accuracy
//----------------------------------------------------------------------------
float UGameHero::GetAccuracy() {
	// Removed
	if (equips[0] > 0) {
		return gameInstance->DataWeapons[equips[0] - 1].accuracy;
	}
	return UGameBattler::GetAccuracy();
}

//----------------------------------------------------------------------------
// * Get Block Rate
//----------------------------------------------------------------------------
float UGameHero::GetBlockRate() {
	// Removed
	if (equips[1] > 0) {
		return gameInstance->DataShields[equips[1] - 1].blockRate;
	}
	return UGameBattler::GetBlockRate();
}

//----------------------------------------------------------------------------
// * Set Stat
//----------------------------------------------------------------------------
void UGameHero::SetStat(int id, int base, int plus) {
	stats[id] = base;
	statPlus[id] = plus;
}

//----------------------------------------------------------------------------
// * Prepare for a Game Load
//----------------------------------------------------------------------------
void UGameHero::PrepForLoad() {
	Abilities.Empty();
}

//----------------------------------------------------------------------------
// * Does the Hero Already Know any Abilities
//----------------------------------------------------------------------------
bool UGameHero::AbilityLearned(int id, bool loading) {
	return Abilities.Find(id) != INDEX_NONE;
}

//----------------------------------------------------------------------------
// * Learn an Ability
//----------------------------------------------------------------------------
void UGameHero::LearnAbility(int id, bool loading) {
	if (!AbilityLearned(id, loading)) {
		Abilities.Add(id);
	}
	
}

//----------------------------------------------------------------------------
// * Forget an Ability
//----------------------------------------------------------------------------
void UGameHero::ForgetAbility(int id, bool loading) {
	for (int i = 0; i < Abilities.Num(); i++) {
		if (Abilities[i] == id) {
			Abilities.RemoveAt(i);
			break;
		}
	}

}