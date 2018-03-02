#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataControl.h"
#include "SubGameInstance.h"
#include "SystemControl.generated.h"

//============================================================================
// * USystemControl
//----------------------------------------------------------------------------
// Static class that manages elements that are kept constant across maps.
//============================================================================
UCLASS()
class DERHOLLERACHE_API USystemControl : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
	
public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "System")
		static void StartNewGame(USubGameInstance*  GameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static UGameAbility *GetAbility(int id, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static TArray<UGameAbility*> &GetAllAbilities(USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static UGameItem *GetItem(int id, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static TArray<UGameItem*> &GetAllItems(USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static UGameStatus *GetStatus(int id, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static TArray<UGameStatus*> &GetAllStatuses(USubGameInstance*  GameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static int GetCurrentMenuIndex(USubGameInstance*  gameInstance);
	UFUNCTION(BlueprintCallable, Category = "System")
		static int SetCurrentMenuIndex(int index, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static int GetCurrentItemPocket(USubGameInstance* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "System")
		static int SetCurrentItemPocket(int index, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "System")
		static int GetCurrentPartyMember(USubGameInstance* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "System")
		static int SetCurrentPartyMember(int index, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Inventory")
		static UGameInventoryItem *GetInventoryItem(int index, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Inventory")
		static TArray<UGameInventoryItem*> &GetPartyInventory(USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Inventory")
		static UGameInventoryItem *FindItem(FString type, int id, USubGameInstance* gameInstance);
	static UGameInventoryItem *FindItem(char type, int id, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Inventory")
		static bool HasItem(FString type, int id, USubGameInstance* gameInstance);
	static bool HasItem(char type, int id, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		static void GainItem(FString type, int id, int quanity, USubGameInstance* gameInstance);
	static void GainItem(char type, int id, int quantity, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		static void LoseItem(FString type, int id, int quanity, USubGameInstance* gameInstance);
	static void LoseItem(char type, int id, int quantity, USubGameInstance* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		static void SortItems(USubGameInstance*  gameInstance);

private:

	//------------------------------------------------------------------------
	// * Private Method Declaration
	//------------------------------------------------------------------------
	static void setupAbilities(USubGameInstance*  gameInstance);
	static void setupItems(USubGameInstance*  gameInstance);
	static void setupStatuses(USubGameInstance*  gameInstance);

	//------------------------------------------------------------------------
	// * Private Class Variable Declaration
	//------------------------------------------------------------------------
	static int lastMenuIndex;
	static int lastItemPocket;
	static int lastHeroSelected;

	//------------------------------------------------------------------------
	// * Private Constant Declaration
	//------------------------------------------------------------------------
	const static int MaxItems;

};
