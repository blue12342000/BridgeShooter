#include "GuidePattern.h"
#include "GameObject.h"
#include "Missile.h"
#include "Unit.h"

void GuidePattern::Move(float deltaTime, GameObject* lpObject)
{
	if (lpObject)
	{
		Transform& transform = lpObject->transform;
		if (typeid(*lpObject) == typeid(Missile))
		{
			Missile* lpMissile = (Missile*)lpObject;
			if (lpMissile->delayTime > 0)
			{
				lpMissile->delayTime -= deltaTime;
				return;
			}

			Unit* lpUnit = lpMissile->GetTarget();
			if (lpUnit)
			{
				transform.angle = atan2(lpUnit->pos.y - lpObject->pos.y, lpUnit->pos.x - lpObject->pos.x);
				while (transform.angle < 0) transform.angle += PI * 2;
				while (transform.angle > PI * 2) transform.angle -= PI * 2;
				float deltaAngle = transform.angle - lpObject->angle;
				if (deltaAngle <= -PI)
				{
					deltaAngle += PI * 2;
				}
				if (abs(deltaAngle) < 0.01f) lpObject->angle = transform.angle;
				else
				{
					lpObject->angle += deltaAngle / (abs(deltaAngle)) * PI * deltaTime;
				}
				lpObject->pos.x += cosf(lpObject->angle) * transform.speed * deltaTime;
				lpObject->pos.y += sinf(lpObject->angle) * transform.speed * deltaTime;
			}
			else
			{
				lpObject->pos.x += cosf(transform.angle) * transform.speed * deltaTime;
				lpObject->pos.y += sinf(transform.angle) * transform.speed * deltaTime;
			}
		}
		else
		{
			lpObject->pos.x += cosf(transform.angle) * transform.speed * deltaTime;
			lpObject->pos.y += sinf(transform.angle) * transform.speed * deltaTime;
		}
	}
}
