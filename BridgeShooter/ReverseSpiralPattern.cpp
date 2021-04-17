#include "ReverseSpiralPattern.h"
#include "GameObject.h"

MoveInfo ReverseSpiralPattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveInfo = {};

	moveInfo.deltaPos.x = -1*cosf(lpObject->angle + sqrt(lpObject->elapsedTime)) * lpObject->elapsedTime * lpObject->speed;
	moveInfo.deltaPos.y = sinf(lpObject->angle + sqrt(lpObject->elapsedTime)) * lpObject->elapsedTime * lpObject->speed;

	return moveInfo;
}
