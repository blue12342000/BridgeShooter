#include "AIController.h"
#include "Unit.h"

void AIController::SetController(Unit* lpUnit)
{
	this->lpUnit = lpUnit;
	lpUnit->SetInetia(true);
}
