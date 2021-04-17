#include "BoomerangPattern.h"
#include "GameObject.h"
MoveInfo BoomerangPattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveinfo = {};
	if (lpObject) 
	{
		isMove = true;
		if ((lpObject->elapsedTime > 2.0f)&& (lpObject->elapsedTime <= 3.0f))
		{
			isMove = false;
		}
		else if ((lpObject->elapsedTime > 3.0f) && (lpObject->elapsedTime <= 3.001f))
		{
			lpObject->angle = atan2((WINSIZE_HEIGHT / 2) - lpObject->pos.y, (WINSIZE_WIDTH / 2) - lpObject->pos.x);
		}
		if (isMove)
		{
			lpObject->pos.x += cos(lpObject->angle) * lpObject->speed * deltaTime;
			lpObject->pos.y += sin(lpObject->angle) * lpObject->speed * deltaTime;
		}
		
	}
	return moveinfo;
}
