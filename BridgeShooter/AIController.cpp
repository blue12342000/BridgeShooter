#include "AIController.h"
#include "Unit.h"

void AIController::SetUnit(Unit* lpUnit)
{
	this->lpUnit = lpUnit;
	lpUnit->SetInetia(true);
}
