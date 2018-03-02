//============================================================================
// * UCombatControl
//----------------------------------------------------------------------------
// Controls all things battle related such as turn order, enemy AI and action
// execution.
//============================================================================
#include "CombatControl.h"
#include <string>

//----------------------------------------------------------------------------
// * Class Variables
//----------------------------------------------------------------------------
TArray<UGameBattler*> UCombatControl::turnOrder;
TArray<CombatAction> UCombatControl::actionQueue;
TArray<UGameBattler*> UCombatControl::currentActionTargets;
TArray<FBattleLog> UCombatControl::newLogs;
TMap<int, int> UCombatControl::enemyCount;

//----------------------------------------------------------------------------
// * Initialize the Enemies
//----------------------------------------------------------------------------
void UCombatControl::InitEnemies(UGameInstance_SP*  gameInstance) {
	for (int i = 0; i < gameInstance->Enemies.Num(); i++) {
		delete gameInstance->Enemies[i];
	}
	gameInstance->Enemies.Empty();
	for (int i = 0; i < gameInstance->DataEnemies.Num(); i++) {
		UGameEnemy *enemy = NewObject<UGameEnemy>();
		enemy->gameInstance = gameInstance;
		enemy->setup(gameInstance->DataEnemies[i].id);
		enemy->AddToRoot();
		gameInstance->Enemies.Add(enemy);
	}
}

//----------------------------------------------------------------------------
// * Get Enemy
//----------------------------------------------------------------------------
UGameEnemy *UCombatControl::GetEnemy(int id, UGameInstance_SP* gameInstance) {
	return gameInstance->Enemies[id - 1];
}

//----------------------------------------------------------------------------
// * Get All Enemy
//----------------------------------------------------------------------------
TArray<UGameEnemy*> &UCombatControl::GetAllEnemies(UGameInstance_SP* gameInstance) {
	return gameInstance->Enemies;
}

//----------------------------------------------------------------------------
// * Add Enemy to Battle
//----------------------------------------------------------------------------
int UCombatControl::AddEnemyToBattle(int id, UGameInstance_SP* gameInstance) {
	int index = gameInstance->EnemyTroop.Num();
	UGameBattleEnemy *enemy = NewObject<UGameBattleEnemy>();
	enemy->gameInstance = gameInstance;
	enemy->create(id, index);
	enemy->AddToRoot();
	gameInstance->EnemyTroop.Add(enemy);
	return index;
}

//----------------------------------------------------------------------------
// * Get Enemy in Troop
//----------------------------------------------------------------------------
UGameBattleEnemy *UCombatControl::GetEnemyInTroop(int index, UGameInstance_SP* gameInstance) {
	return gameInstance->EnemyTroop[index];
}

//----------------------------------------------------------------------------
// * Get All Enemies in Troop
//----------------------------------------------------------------------------
TArray<UGameBattleEnemy*> &UCombatControl::GetAllEnemiesInTroop(UGameInstance_SP* gameInstance) {
	return gameInstance->EnemyTroop;
}

//----------------------------------------------------------------------------
// * Get All Enemies in Troop
//----------------------------------------------------------------------------
TArray<UGameBattler*> &UCombatControl::GetAllBattlers(UGameInstance_SP* gameInstance) {
	return turnOrder;
}

//----------------------------------------------------------------------------
// * Prepare the Battle
//----------------------------------------------------------------------------
void UCombatControl::PrepareBattle(UGameInstance_SP* gameInstance) {
	actionQueue.Empty();
	currentActionTargets.Empty();
	newLogs.Empty();
	for (int i = 0; i < gameInstance->EnemyTroop.Num(); i++) {
		delete gameInstance->EnemyTroop[i];
	}
	gameInstance->EnemyTroop.Empty();
}

//----------------------------------------------------------------------------
// * Initialize the Battle
//----------------------------------------------------------------------------
void UCombatControl::InitBattle(UGameInstance_SP* gameInstance) {
	setupTurnOrder(gameInstance);
}

//----------------------------------------------------------------------------
// * Setup Turn Order
//----------------------------------------------------------------------------
void UCombatControl::setupTurnOrder(UGameInstance_SP* gameInstance) {
	turnOrder.Empty();
	for (int i = 0; i < gameInstance->Party.Num(); i++) {
		turnOrder.Add(gameInstance->Party[i]);
	}
	for (int i = 0; i < gameInstance->EnemyTroop.Num(); i++) {
		turnOrder.Add(gameInstance->EnemyTroop[i]);
	}
	for (int i = 0; i < turnOrder.Num(); i++) {
		if (turnOrder[i] == NULL) {
			turnOrder.RemoveAt(i);
		}
	}
	SortTurns(gameInstance);
}

//----------------------------------------------------------------------------
// * Sort Turns
//----------------------------------------------------------------------------
void UCombatControl::SortTurns(UGameInstance_SP* gameInstance) {
	turnOrder.Sort([](UGameBattler &A, UGameBattler &B) {
		if (A.GetSpeed() == B.GetSpeed()) {
			return FMath::RandBool();
		} else {
			return A.GetSpeed() > B.GetSpeed();
		} 
	});
}

//----------------------------------------------------------------------------
// * Get the Battler Who's Turn It Current Is
//----------------------------------------------------------------------------
UGameBattler *UCombatControl::GetActingBattler(UGameInstance_SP* gameInstance) {
	return turnOrder[0];
}

//----------------------------------------------------------------------------
// * End Turn
//----------------------------------------------------------------------------
TArray<FBattleLog> UCombatControl::EndTurn(UGameInstance_SP* gameInstance) {
	TArray<FBattleLog> logs;
	for (int i = 0; i < GetActingBattler(gameInstance)->StatusConditions.Num(); i++) {
		switch (GetActingBattler(gameInstance)->StatusConditions[i]->GetID()) {
		case 1: // Poison
			logs.Add({ "Poison", GetActingBattler(gameInstance), GetActingBattler(gameInstance), GetActingBattler(gameInstance)->GetCurrentHP() / 10 });
			GetActingBattler(gameInstance)->TakeDamage(GetActingBattler(gameInstance)->GetCurrentHP() / 10);
			break;
		}
	}
	shiftTurnOrder(gameInstance);
	return logs;
}

//----------------------------------------------------------------------------
// * Shift Turn Order
//----------------------------------------------------------------------------
void UCombatControl::shiftTurnOrder(UGameInstance_SP* gameInstance) {
	UGameBattler *battler = turnOrder[0];
	turnOrder.Add(battler);
	turnOrder.RemoveAt(0);
}

//----------------------------------------------------------------------------
// * Queue an Action for Usage in Battle
//----------------------------------------------------------------------------
void UCombatControl::QueueAction(FString type, int id, UGameInstance_SP* gameInstance) {
	std::string trueType(TCHAR_TO_UTF8(*type));
	QueueAction(trueType[0], id, gameInstance);
}

void UCombatControl::QueueAction(char type, int id, UGameInstance_SP* gameInstance) {
	CombatAction action;
	switch (type) {
	case 'A':
		action.action = USystemControl::GetAbility(id, gameInstance);
		action.user = GetActingBattler(gameInstance);
		action.targets = currentActionTargets;
		actionQueue.Add(action);
		break;
	case 'I':
		action.action = USystemControl::GetItem(id, gameInstance);
		action.user = GetActingBattler(gameInstance);
		action.targets = currentActionTargets;
		actionQueue.Add(action);
		break;
	}
}

//----------------------------------------------------------------------------
// * Parse All Possible Targets for an Action
//----------------------------------------------------------------------------
TArray<UGameBattler*> &UCombatControl::ParseActionTarget(UGameBattler *user, UGameAction *action, UGameInstance_SP* gameInstance) {
	currentActionTargets.Empty();
	TArray<UGameBattler*> userSide;
	TArray<UGameBattler*> foeSide;
	if (user->IsHero()) {
		for (int i = 0; i < gameInstance->Party.Num(); i++) {
			userSide.Add(gameInstance->Party[i]);
		}
		for (int i = 0; i < gameInstance->EnemyTroop.Num(); i++) {
			foeSide.Add(gameInstance->EnemyTroop[i]);
		}
	} else {
		for (int i = 0; i < gameInstance->EnemyTroop.Num(); i++) {
			userSide.Add(gameInstance->EnemyTroop[i]);
		}
		for (int i = 0; i < gameInstance->Party.Num(); i++) {
			foeSide.Add(gameInstance->Party[i]);
		}
	}
	switch (action->GetTarget()) {
	case 0: // Single Target but User
	case 8: // All Battlers but User
		for (int i = 0; i < userSide.Num(); i++) {
			if (userSide[i] == user || userSide[i]->IsDead()) {
				continue;
			}
			currentActionTargets.Add(userSide[i]);
		}
		for (int i = 0; i < foeSide.Num(); i++) {
			if (foeSide[i]->IsDead()) {
				continue;
			}
			currentActionTargets.Add(foeSide[i]);
		}
		break;
	case 1: // No Target
		break;
	case 2: // Single Random Foe
	case 4: // All Foes
		for (int i = 0; i < foeSide.Num(); i++) {
			if (foeSide[i]->IsDead()) {
				continue;
			}
			currentActionTargets.Add(foeSide[i]);
		}
		break;
	case 10: // User
		currentActionTargets.Add(user);
		break;
	case 20: // Both Sides
		for (int i = 0; i < userSide.Num(); i++) {
			if (userSide[i]->IsDead()) {
				continue;
			}
			currentActionTargets.Add(userSide[i]);
		}
		for (int i = 0; i < foeSide.Num(); i++) {
			if (foeSide[i]->IsDead()) {
				continue;
			}
			currentActionTargets.Add(foeSide[i]);
		}
		break;
	case 40: // User's Side
	case 200: // Single Battler on User's Side
		for (int i = 0; i < userSide.Num(); i++) {
			if (userSide[i]->IsDead()) {
				continue;
			}
			currentActionTargets.Add(userSide[i]);
		}
		break;
	case 80: // Foe's Side
		for (int i = 0; i < foeSide.Num(); i++) {
			if (foeSide[i]->IsDead()) {
				continue;
			}
			currentActionTargets.Add(foeSide[i]);
		}
		break;

	case 400: // Single Slain Ally
		for (int i = 0; i < userSide.Num(); i++) {
			if (userSide[i]->IsDead()) {
				currentActionTargets.Add(userSide[i]);
			}
		}
		break;
	}
	return currentActionTargets;
}

//----------------------------------------------------------------------------
// * Queue an Action for Usage in Battle
//----------------------------------------------------------------------------
TArray<UGameBattler*> &UCombatControl::FinalizeActionTarget(UGameAction *action, UGameBattler *target, UGameInstance_SP* gameInstance) {
	switch (action->GetTarget()) {
	case 0: // Single Target but User
	case 200: // Single Battler on User's Side
	case 10: // User
		actionQueue[0].targets.Empty();
		actionQueue[0].targets.Add(target);
		break;
	case 2: // Single Random Target
		actionQueue[0].targets.Empty();
		actionQueue[0].targets.Add(currentActionTargets[FMath::RandRange(0, currentActionTargets.Num())]);
		break;
	case 1: // No Target
		actionQueue[0].targets.Empty();
		break;
	default: // Target All
		actionQueue[0].targets.Empty();
		for (int i = 0; i < currentActionTargets.Num(); i++) {
			actionQueue[0].targets.Add(currentActionTargets[i]);
		}
		break;
	}
	currentActionTargets.Empty();
	return actionQueue[0].targets;
}

//----------------------------------------------------------------------------
// * Prepare the Action at the Head of the Queue
//----------------------------------------------------------------------------
TArray<FBattleLog> &UCombatControl::PrepAction(UGameInstance_SP* gameInstance) {
	newLogs.Empty();
	if (actionQueue.Num() > 0) {
		CombatAction action = actionQueue[0];
		int cat = action.action->GetCategory();
		TArray<int> dmg;
		TArray<bool> crits;
		bool isPhysical = false;
		bool ignoreDefense = action.action->GetFunctionCode() == 0x001 || action.action->GetFunctionCode() == 0x002;
		switch (cat) {
		case 0: // Physical
			for (int i = 0; i < action.targets.Num(); i++) {
				isPhysical = true;
				int atk = action.user->GetAttack();
				int def = ignoreDefense ? 0 : action.targets[i]->GetDefense();
				float rate = 1.0f;
				for (int j = 0; j < action.action->GetElements().Num(); j++) {
					rate *= action.targets[i]->ElementRate(action.action->GetElements()[j]);
				}
				bool crit = action.user->CheckCrit(action.action);
				bool guard = action.targets[i]->IsGuarding();
				dmg.Add(action.action->EvalDamage(atk, def, rate, crit, guard));
				crits.Add(crit);
			}
			break;
		case 1: // Magic
			for (int i = 0; i < action.targets.Num(); i++) {
				int atk = action.user->GetMagic();
				int def = ignoreDefense ? 0 : action.targets[i]->GetResistance();
				float rate = 1.0f;
				for (int j = 0; j < action.action->GetElements().Num(); j++) {
					rate *= action.targets[i]->ElementRate(action.action->GetElements()[j]);
				}
				bool crit = action.user->CheckCrit(action.action);
				bool guard = action.targets[i]->IsGuarding();
				dmg.Add(action.action->EvalDamage(atk, def, rate, crit, guard));
				crits.Add(crit);
			}
			break;
		default: // Status
			if (action.action->GetPower() > 0) {
				for (int i = 0; i < action.targets.Num(); i++) {
					float rate = 1.0f;
					for (int j = 0; j < action.action->GetElements().Num(); j++) {
						rate *= action.targets[i]->ElementRate(action.action->GetElements()[j]);
					}
					bool crit = false;
					bool guard = false;
					dmg.Add(action.action->EvalDamage(0, 0, rate, false, false));
					crits.Add(crit);
				}
			} else {
				for (int i = 0; i < action.targets.Num(); i++) {
					dmg.Add(0);
					crits.Add(false);
				}
			}
			break;
		}
		for (int i = 0; i < dmg.Num(); i++) {
			float accur = isPhysical ? action.user->GetAccuracy() : 1.0f;
			float block = isPhysical ? action.targets[i]->GetBlockRate() : 0.0f;
			if (action.action->EvalHit(accur, block)) {
				// Primary Damage Effect
				if (cat != 2 || dmg[i] > 0) {
					if (action.action->GetFunctionCode() == 0x001) { // Heal
						newLogs.Add({ "Heal", action.user, action.targets[i], dmg[i] });
					} else if (action.action->GetFunctionCode() == 0x003) {
						newLogs.Add({ "MP Heal", action.user, action.targets[i], dmg[i] });
					} else {
						if (crits[i]) {
							newLogs.Add({ "Critical", action.user, action.targets[i], 1 });
						}
						newLogs.Add({ "Damage", action.user, action.targets[i], dmg[i] });
					}
				}
				// Secondary Effect
				switch (action.action->GetFunctionCode()) { 
				case 0x004: // Inflict Poison
					if (FMath::RandRange(0.0f, 1.0f) < 0.3f) {
						newLogs.Add({ "Status", action.user, action.targets[i], 1 });
					}
					break;
				}
			} else {
newLogs.Add({ "Miss", action.user, action.targets[i], dmg[i] });
			}
		}
		actionQueue.RemoveAt(0);
	}
	return newLogs;
}

//----------------------------------------------------------------------------
// * Execute the Action Effect
//----------------------------------------------------------------------------
void UCombatControl::ExecuteActionEffect(FBattleLog action, UGameInstance_SP* gameInstance) {
	if (action.Type == "Damage") {
		action.Target->TakeDamage(action.EffectValue);
	} else if (action.Type == "Heal") {
		action.Target->Heal(action.EffectValue);
	} else if (action.Type == "MP Heal") {
		action.Target->HealMP(action.EffectValue);
	}
}

//----------------------------------------------------------------------------
// * Terminate the Current Action Target
//----------------------------------------------------------------------------
void UCombatControl::TerminateCurrentAction(UGameInstance_SP* gameInstance) {
	actionQueue.RemoveAt(0);
	newLogs.Empty();
	currentActionTargets.Empty();
}

//----------------------------------------------------------------------------
// * Get the Current Action
//----------------------------------------------------------------------------
UGameAction *UCombatControl::GetCurrentAction(UGameInstance_SP* gameInstance) {
	return actionQueue[0].action;
}

//----------------------------------------------------------------------------
// * Clear Action Queue
//----------------------------------------------------------------------------
void UCombatControl::ClearActionQueue(UGameInstance_SP* gameInstance) {
	actionQueue.Empty();
	currentActionTargets.Empty();
	newLogs.Empty();
}

//----------------------------------------------------------------------------
// * Clear Action Queue
//----------------------------------------------------------------------------
UGameBattler *UCombatControl::SelectEnemyAction(UGameBattleEnemy *enemy, UGameInstance_SP* gameInstance) {
	enemy->pickAction();
	char type = enemy->selectedAction.type == 0 ? 'A' : 'I';
	QueueAction(type, enemy->selectedAction.itemId, gameInstance);
	ParseActionTarget(enemy, actionQueue[0].action, gameInstance);
	int targ;
	switch (actionQueue[0].action->GetTarget()) {
	case 0: // Single Target
		targ = FMath::RandRange(0, currentActionTargets.Num() - 1);
		while (currentActionTargets[targ]->IsEnemy()) {
			currentActionTargets.RemoveAt(targ);
			targ = FMath::RandRange(0, currentActionTargets.Num() - 1);
		}
		return currentActionTargets[targ];
	default:
		targ = FMath::RandRange(0, currentActionTargets.Num() - 1);
		return currentActionTargets[targ];
	}
}

//----------------------------------------------------------------------------
// * Judge Win/Loss
//----------------------------------------------------------------------------
int UCombatControl::JudgeWinLoss(UGameInstance_SP* gameInstance, bool abort) {
	if (abort) {
		return 3; // Abort
	} else if (UPartyControl::AllDead(gameInstance)) {
		return 2; // Party Wipe
	} else if (AllEnemiesDead(gameInstance)) {
		return 1; // Victory
	} else {
		return 0;
	}
}

//----------------------------------------------------------------------------
// * All Enemies Dead
//----------------------------------------------------------------------------
bool UCombatControl::AllEnemiesDead(UGameInstance_SP* gameInstance) {
	for (int i = 0; i < gameInstance->EnemyTroop.Num(); i++) {
		if (!gameInstance->EnemyTroop[i]->IsDead()) {
			return false;
		}
	}
	return true;
}

//----------------------------------------------------------------------------
// * Called on Battle End
//----------------------------------------------------------------------------
void UCombatControl::BattleEnd(UGameInstance_SP* gameInstance) {
	for (int i = 0; i < gameInstance->Party.Num(); i++) {
		gameInstance->Party[i]->ClearStatusConditions();
	}
}

//----------------------------------------------------------------------------
// * Create a Temp Queue for Action Use
//----------------------------------------------------------------------------
void UCombatControl::CreateTempTurns(UGameHero *hero, UGameInstance_SP* gameInstance) {
	turnOrder.Empty();
	turnOrder.Add(hero);
}