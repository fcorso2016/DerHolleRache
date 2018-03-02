#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataControl.h"
#include "GameStatus.generated.h"

//============================================================================
// * UGameStatus
//----------------------------------------------------------------------------
// Sets all the statuses on enemies in the game.
//============================================================================
UCLASS()
class DERHOLLERACHE_API UGameStatus : public UObject {

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UGameStatus();
	~UGameStatus();
	void setID(int id);
	FData_Status getStatusData();
	UFUNCTION(Blueprintpure, Category = "StatusConditions")
		int GetID();
	UFUNCTION(BlueprintPure, Category = "StatusConditions")
		FName GetName();
	UFUNCTION(BlueprintPure, Category = "StatusConditions")
		int GetFunctionCode();

	UPROPERTY()
		UDataGameInstance* gameInstance;

private:
	//------------------------------------------------------------------------
	// * Private Instance Variable Declaration
	//------------------------------------------------------------------------
	int statusId;

	GENERATED_BODY()
	
};
