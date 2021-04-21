#include "AIController.h"
#include "Unit.h"

void AIController::SetUnit(Unit* lpUnit)
{
	this->lpUnit = lpUnit;
	this->lpUnit->SetInetia(true);
	this->lpUnit->SetUnitKind(UNIT_KIND::ENEMY);
}
