#include "BoomerangPattern.h"
#include "GameObject.h"
void BoomerangPattern::Move(float deltaTime, GameObject* lpObject)
{
	if (lpObject) {
		if (deltaTime == 0.900f) {
			lpObject->angle= lpObject->angle+PI;
		}
		lpObject->pos.x = cos(lpObject->angle) * lpObject->speed * deltaTime;
		lpObject->pos.y = sin(lpObject->angle) * lpObject->speed * deltaTime;
	}
	
}
