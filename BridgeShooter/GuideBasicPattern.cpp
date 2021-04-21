#include "GuideBasicPattern.h"
#include "Missile.h"
#include "Unit.h"

void GuideBasicPattern::Move(float deltaTime, GameObject* lpObject)
{
	if (lpObject)
	{
		Transform& transform = lpObject->transform;
		if (typeid(*lpObject) == typeid(Missile))
		{
			Missile* lpMissile = (Missile*)lpObject;
			Unit* lpUnit = lpMissile->GetTarget();
			if (lpUnit)
			{
				lpObject->angle = atan2(lpUnit->pos.y - lpObject->pos.y, lpUnit->pos.x - lpObject->pos.x);
			}
			if (lpMissile->delayTime > 0)
			{
				lpMissile->delayTime -= deltaTime;
				return;
			}

			lpObject->pos.x += cosf(lpObject->angle) * transform.speed * deltaTime;
			lpObject->pos.y += sinf(lpObject->angle) * transform.speed * deltaTime;
		}
		else
		{
			lpObject->pos.x += cosf(lpObject->angle) * transform.speed * deltaTime;
			lpObject->pos.y += sinf(lpObject->angle) * transform.speed * deltaTime;
		}
	}
}
