#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "GameAction.h"
#include "GameAbility.generated.h"

//============================================================================
// * UGameAbility
//----------------------------------------------------------------------------
// Extends UGameAction for the purpose of abilities.
//============================================================================
UCLASS(Blueprintable)
class DERHOLLERACHE_API UGameAbility : public UGameAction {

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameAbility();
	~UGameAbility();
	UFUNCTION(BlueprintPure, Category = "Action")
		int GetMPCost();
	UFUNCTION(BlueprintPure, Category = "Action")
		virtual bool IsAbility();
	UFUNCTION(BlueprintPure, Category = "Action")
		virtual bool IsItem();


protected:
	//------------------------------------------------------------------------
	// * Protected Method Declaration
	//------------------------------------------------------------------------
	virtual FData_Action getActionData();
	FData_Ability getAbilityData();

	GENERATED_BODY()
};
