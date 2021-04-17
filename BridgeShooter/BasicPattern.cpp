#include "BasicPattern.h"
#include "GameObject.h"

MoveInfo BasicPattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveInfo = { 0, 0 };
	lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
	lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;

	return moveInfo;
}
