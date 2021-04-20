#include "CircleMovePattern.h"
#include "GameObject.h"

MoveInfo CircleMovePattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveInfo = { 0, 0 };

    moveInfo.deltaPos.x = cosf(lpObject->angle + lpObject->elapsedTime * PI) * lpObject->speed;
    moveInfo.deltaPos.y = sinf(lpObject->angle + lpObject->elapsedTime * PI) * lpObject->speed;

    return moveInfo;
}
