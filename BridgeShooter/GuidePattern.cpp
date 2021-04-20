#include "GuidePattern.h"
#include "GameObject.h"
#include "Missile.h"
#include "Unit.h"

MoveInfo GuidePattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveInfo = { 0, 0 };

	if (lpObject)
	{
		if (typeid(*lpObject) == typeid(Missile))
		{
			Missile* lpMissile = (Missile*)lpObject;
			Unit* lpUnit = lpMissile->GetTarget();
			if (lpUnit)
			{
				lpObject->originAngle = atan2(lpUnit->pos.y - lpObject->pos.y, lpUnit->pos.x - lpObject->pos.x);
				while (lpObject->angle < 0) lpObject->angle += PI * 2;
				while (lpObject->angle > PI * 2) lpObject->angle -= PI * 2;
				float deltaAngle = lpObject->originAngle - lpObject->angle;
				if (deltaAngle <= -PI)
				{
					deltaAngle += PI * 2;
				}
				if (abs(deltaAngle) < 0.01f) lpObject->angle = lpObject->originAngle;
				else
				{
					lpObject->angle += deltaAngle / (abs(deltaAngle)) * PI * deltaTime;
				}
				lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
				lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;
			}
			else
			{
				lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
				lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;
			}
		}
		else
		{
			lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
			lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;
		}
	}

	return moveInfo;
}
