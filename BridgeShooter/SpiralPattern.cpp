#include "SpiralPattern.h"
#include "GameObject.h"

MoveInfo SpiralPattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveInfo = {};

    moveInfo.deltaPos.x = cosf(lpObject->angle + sqrt(lpObject->elapsedTime)) * lpObject->elapsedTime * lpObject->speed;
    moveInfo.deltaPos.y = sinf(lpObject->angle + sqrt(lpObject->elapsedTime)) * lpObject->elapsedTime * lpObject->speed;

    return moveInfo;
}
