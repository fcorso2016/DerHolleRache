//============================================================================
// * UGameStatus
//----------------------------------------------------------------------------
// Sets all the statuses on enemies in the game.
//============================================================================
#include "GameStatus.h"

//----------------------------------------------------------------------------
// * Object Initialization
//----------------------------------------------------------------------------
UGameStatus::UGameStatus() {

}

//----------------------------------------------------------------------------
// * Object Destruction
//----------------------------------------------------------------------------
UGameStatus::~UGameStatus() {

}

//----------------------------------------------------------------------------
// * Set ID
//----------------------------------------------------------------------------
void UGameStatus::setID(int id) {
	statusId = id;
}

//----------------------------------------------------------------------------
// * Get Data Class
//----------------------------------------------------------------------------
FData_Status UGameStatus::getStatusData() {
	// Removed
	return gameInstance->DataStatuses[statusId - 1];
}

//----------------------------------------------------------------------------
// * Get ID
//----------------------------------------------------------------------------
int UGameStatus::GetID() {
	return statusId;
}

//----------------------------------------------------------------------------
// * Get Name
//----------------------------------------------------------------------------
FName UGameStatus::GetName() {
	return getStatusData().name;
}

//----------------------------------------------------------------------------
// * Get Function Code
//----------------------------------------------------------------------------
int UGameStatus::GetFunctionCode() {
	return getStatusData().functionCode;
}