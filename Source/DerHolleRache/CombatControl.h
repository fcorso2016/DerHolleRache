#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Map.h"
#include "PartyControl.h"
#include "GameInstance_SP.h"
#include "CombatControl.generated.h"

//============================================================================
// * CombatAction
//----------------------------------------------------------------------------
// Struct that stores the address of both the selected action and the user.
//============================================================================
struct CombatAction {
	UGameAction *action;
	UGameBattler *user;
	TArray<UGameBattler*> targets;

};

//============================================================================
// * FBattleLog
//----------------------------------------------------------------------------
// Struct that stores the data of a combat log entry.
//============================================================================
USTRUCT(Blueprintable)
struct FBattleLog {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
		FName Type;
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
		UGameBattler *User;
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
		UGameBattler *Target;
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
		int EffectValue;
};

//============================================================================
// * UCombatControl
//----------------------------------------------------------------------------
// Controls all things battle related such as turn order, enemy AI and action
// execution.
//============================================================================
UCLASS()
class DERHOLLERACHE_API UCombatControl : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void InitEnemies(UGameInstance_SP*  gameInstance);
	UFUNCTION(BlueprintPure, Category = "Combat")
		static UGameEnemy *GetEnemy(int id, UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Combat")
		static TArray<UGameEnemy*> &GetAllEnemies(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static int AddEnemyToBattle(int id, UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Combat")
		static UGameBattleEnemy *GetEnemyInTroop(int index, UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Combat")
		static TArray<UGameBattleEnemy*> &GetAllEnemiesInTroop(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Combat")
		static TArray<UGameBattler*> &GetAllBattlers(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void PrepareBattle(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void InitBattle(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static TArray<FBattleLog> EndTurn(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Combat")
		static UGameBattler *GetActingBattler(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void QueueAction(FString type, int id, UGameInstance_SP* gameInstance);
	static void QueueAction(char type, int id, UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static TArray<UGameBattler*> &ParseActionTarget(UGameBattler *user, UGameAction *action, UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static TArray<UGameBattler*> &FinalizeActionTarget(UGameAction *action, UGameBattler *target, UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static TArray<FBattleLog> &PrepAction(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void ExecuteActionEffect(FBattleLog action, UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void TerminateCurrentAction(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Combat")
		static UGameAction *GetCurrentAction(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void ClearActionQueue(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void SortTurns(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static UGameBattler *SelectEnemyAction(UGameBattleEnemy *enemy, UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static int JudgeWinLoss(UGameInstance_SP* gameInstance, bool abort = false);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static bool AllEnemiesDead(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void BattleEnd(UGameInstance_SP* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void CreateTempTurns(UGameHero *hero, UGameInstance_SP* gameInstance);

protected:
	//------------------------------------------------------------------------
	// * Protected Method Declaration
	//------------------------------------------------------------------------
	static void setupTurnOrder(UGameInstance_SP* gameInstance);
	static void shiftTurnOrder(UGameInstance_SP* gameInstance);

	//------------------------------------------------------------------------
	// * Protected Class Variable Declaration
	//------------------------------------------------------------------------
	static TArray<UGameBattler*> turnOrder;
	static TArray<CombatAction> actionQueue;
	static TArray<UGameBattler*> currentActionTargets;
	static TArray<FBattleLog> newLogs;
	static TMap<int, int> enemyCount;
	
};
