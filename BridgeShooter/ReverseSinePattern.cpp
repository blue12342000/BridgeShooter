#include "ReverseSinePattern.h"
#include "BridgeShooter.h"
#include "GameObject.h"

MoveInfo ReverseSinePattern::Move(float deltaTime, GameObject* lpObject)
{
	int count = 0;
	MoveInfo moveInfo = { 0, 0 };
	if (lpObject)
	{
	
		/*
		moveInfo.angle = lpObject->angle + sqrt(lpObject->elapsedTime);
		moveInfo.deltaPos.x = cosf(lpObject->angle  ) * lpObject->elapsedTime * lpObject->speed;
		moveInfo.deltaPos.y = sinf(lpObject->angle + lpObject->elapsedTime) * lpObject->elapsedTime * lpObject->speed;
		*/
		++count;
		moveInfo.angle = lpObject->angle+= PI/64* elapsedTime;
		moveInfo.deltaPos.x = cosf(lpObject->angle) * lpObject->elapsedTime * lpObject->speed;
		moveInfo.deltaPos.y = sinf(lpObject->angle) * lpObject->elapsedTime * lpObject->speed;
		if (count <= 5) count *= -6;
	}
	return moveInfo;
}
