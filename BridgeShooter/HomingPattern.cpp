#include "HomingPattern.h"
#include "GameObject.h"
#include "Planet.h"


void HomingPattern::Move(float deltaTime, GameObject* lpObject)
{
		
	if (lpObject)
	{
		elapsedTime *= -1;
		lpObject->pos.x += cosf(lpObject->angle* elapsedTime) * lpObject->speed * deltaTime;
		lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;

	}

}
