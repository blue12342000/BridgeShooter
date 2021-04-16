#include "HomingPattern.h"
#include "GameObject.h"
#include "BridgeShooter.h"

void HomingPattern::Move(float deltaTime, GameObject* lpObject)
{
	/*
	float elapsedTime = lpObject->elapsedTime;
	if (lpObject)
	{
		lpObject->angle = GetAngle(pos, lpObject->pos);
		float ratio = (lpObject->angle - angle) / 50.0f;

		if (-0.01f < ratio && ratio < 0.01f)
		{
			angle = destAngle;
		}
		else
		{
			angle += ratio;
		}
	}

	lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
	lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;
	*/

}
