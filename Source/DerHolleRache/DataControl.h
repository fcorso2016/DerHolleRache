#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataGameInstance.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "DataControl.generated.h"

//============================================================================
// * UDataControl
//----------------------------------------------------------------------------
// Static class that creates all the data structures used by the game.
//============================================================================
UCLASS()
class DERHOLLERACHE_API UDataControl : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UFUNCTION(BlueprintPure, Category = "Database")
		static FName GetStat(int id, UDataGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Database")
		static FName GetElement(int id, UDataGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Database")
		static FName GetEquipSlot(int index, UDataGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Database")
		static FName GetWeaponType(int id, UDataGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Database")
		static FName GetShieldType(int id, UDataGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Database")
		static FName GetArmorType(int id, UDataGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Database")
		static FName GetPocket(int id, UDataGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Database")
		static FName GetItemName(FString type, int id, UDataGameInstance* gameInstance);
	static FName GetItemName(char type, int id, UDataGameInstance* gameInstance);

	//------------------------------------------------------------------------
	// * Private Class Variable Declaration
	//------------------------------------------------------------------------
	static UDataGameInstance* gameInstance;
	
};