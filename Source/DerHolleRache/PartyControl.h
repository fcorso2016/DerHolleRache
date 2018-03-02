#pragma once

//----------------------------------------------------------------------------
// * Included Modules
//----------------------------------------------------------------------------
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IntermediateGameInstance.h"
#include "PartyControl.generated.h"

//============================================================================
// * UPartyControl
//----------------------------------------------------------------------------
// Static class that manages the party and party related things.
//============================================================================
UCLASS()
class DERHOLLERACHE_API UPartyControl : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
	
public:
	//------------------------------------------------------------------------
	// * Public Method Declaration
	//------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "Party")
		static void InitHeros(UIntermediateGameInstance*  GameInstance);
	UFUNCTION(BlueprintCallable, Category = "Loading")
		static void PrepForLoad(UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Party")
		static UGameHero *GetHero(int id, UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Party")
		static TArray<UGameHero*> &GetAllHeros(UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Party")
		static UGameHero *GetPartyMember(int index, UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Party")
		static UGameHero *GetPartyLeader(UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Party")
		static TArray<UGameHero*> &GetAllPartyMembers(UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Party")
		static bool AllDead(UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Party")
		static void AddToParty(int id, UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintCallable, Category = "Party")
		static void RemoveFromParty(int id, UIntermediateGameInstance* gameInstance);
	UFUNCTION(BlueprintPure, Category = "Party")
		static bool CurrentlyInParty(int id, UIntermediateGameInstance* gameInstance);
	
private:
	//------------------------------------------------------------------------
	// * Private Method Declaration
	//------------------------------------------------------------------------
	static void setupHeros(UIntermediateGameInstance* gameInstance);
	static void setupParty(UIntermediateGameInstance* gameInstance);

	//------------------------------------------------------------------------
	// * Private Constant Declaration
	//------------------------------------------------------------------------
	const static int StartingParty[1];
	
};
