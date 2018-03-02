#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "GameAction.h"
#include "GameItem.generated.h"

//============================================================================
// * UGameItem
//----------------------------------------------------------------------------
// Extends UGameAction for the purpose of items.
//============================================================================
UCLASS(Blueprintable)
class DERHOLLERACHE_API UGameItem : public UGameAction {

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameItem();
	~UGameItem();
	UFUNCTION(BlueprintPure, Category = "Action")
		bool IsConsumable();
	UFUNCTION(BlueprintPure, Category = "Action")
		bool IsKeyItem();
	UFUNCTION(BlueprintPure, Category = "Action")
		int GetPocket();
	UFUNCTION(BlueprintPure, Category = "Action")
		virtual bool IsAbility();
	UFUNCTION(BlueprintPure, Category = "Action")
		virtual bool IsItem();


protected:
	//------------------------------------------------------------------------
	// * Protected Method Declaration
	//------------------------------------------------------------------------
	virtual FData_Action getActionData();
	FData_Item getItemData();

	GENERATED_BODY()

};
