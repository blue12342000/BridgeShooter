#include "Unit.h"
#include"Factory.h"
void Unit::SetFactory(Factory* lpFactory)
{
	this->lpFactory = lpFactory;
}
void Unit::fire(void)
{
	lpFactory->Fire(this);
}
