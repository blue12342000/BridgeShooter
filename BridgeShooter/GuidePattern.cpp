#include "GuidePattern.h"
#include "GameObject.h"
#include "Missile.h"

MoveInfo GuidePattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveInfo = { 0, 0 };

	if (lpObject)
	{
		if (typeid(*lpObject) == typeid(Missile))
		{

		}
	}

	return moveInfo;
}
