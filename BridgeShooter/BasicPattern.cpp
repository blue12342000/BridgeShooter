#include "BasicPattern.h"
#include "GameObject.h"

void BasicPattern::Move(float deltaTime, GameObject* lpObject)
{
	lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
	lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;
}
