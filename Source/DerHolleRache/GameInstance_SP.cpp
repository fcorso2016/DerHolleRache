//============================================================================
// * UGameInstance_SP
//----------------------------------------------------------------------------
// Game Instance object that keeps a copy of all data members in order to
// protect them from garbage collection.
//============================================================================
#include "GameInstance_SP.h"

void UGameInstance_SP::StoreSelf() {
	MemoryAddress = this;
}