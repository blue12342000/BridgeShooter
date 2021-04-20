#include "AIController.h"
#include "Unit.h"

void AIController::SetController(Unit* lpUnit)
{
	this->lpUnit = lpUnit;
	origin = lpUnit->pos;
	lpUnit->SetInetia(true);
}
