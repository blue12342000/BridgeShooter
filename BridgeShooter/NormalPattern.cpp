#include "NormalPattern.h"
#include "GameObject.h"
#include"Missile.h"
MoveInfo NormalPattern::Move(float deltaTime, GameObject* lpObject)
{
	MoveInfo moveInfo{};
	if (lpObject) {
		lpObject->pos.x += cos(lpObject->angle) * lpObject->speed * deltaTime;
		lpObject->pos.y += sin(lpObject->angle) * lpObject->speed * deltaTime;
	}
	return moveInfo;
}
