#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataControl.h"
#include "GameAction.generated.h"

//============================================================================
// * UGameAction
//----------------------------------------------------------------------------
// Sets up actions for usage by battlers.
//============================================================================
UCLASS(Blueprintable)
class DERHOLLERACHE_API UGameAction : public UObject {

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameAction();
	~UGameAction();
	void setID(int id);
	UFUNCTION(BlueprintPure, Category = "Action")
		int GetID();
	UFUNCTION(BlueprintPure, Category = "Action")
		FName GetName();
	UFUNCTION(BlueprintPure, Category = "Action")
		FText GetDescription();
	UFUNCTION(BlueprintPure, Category = "Action")
		int GetCategory();
	UFUNCTION(BlueprintPure, Category = "Action")
		int GetPower();
	UFUNCTION(BlueprintPure, Category = "Action")
		float GetAccuracy();
	UFUNCTION(BlueprintPure, Category = "Action")
		int GetFunctionCode();
	UFUNCTION(BlueprintPure, Category = "Action")
		int GetTarget();
	UFUNCTION(BlueprintPure, Category = "Action")
		TArray<int> GetElements();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool UsableInField();
	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool UsableInBattle();
	UFUNCTION(BlueprintCallable, Category = "Action")
		int EvalDamage(int atk, int def, float rate = 1.0f, bool crit = false, bool guard = false);
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool EvalHit(float weaponAccuracy = 1.0f, float blockRate = 0.0f);
	UFUNCTION(BlueprintPure, Category = "Action")
		bool NeedsSelection();
	UFUNCTION(BlueprintPure, Category = "Action")
		virtual bool IsAbility();
	UFUNCTION(BlueprintPure, Category = "Action")
		virtual bool IsItem();

	UPROPERTY()
		UDataGameInstance* gameInstance;

protected:
	//------------------------------------------------------------------------
	// * Protected Method Declaration
	//------------------------------------------------------------------------
	virtual FData_Action getActionData();

	//------------------------------------------------------------------------
	// * Protected Instance Variable Declaration
	//------------------------------------------------------------------------
	int id;

	//------------------------------------------------------------------------
	// * Protected Class Variable Declaration
	//------------------------------------------------------------------------
	static FData_Action DummyAction;

	GENERATED_BODY()
};
