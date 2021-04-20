#include "CircleMovePattern.h"
#include "GameObject.h"

MoveInfo CircleMovePattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveInfo = { 0, 0 };

    moveInfo.deltaPos.x = cosf(-PI / 2 + lpObject->elapsedTime * 2) * lpObject->speed / 2;
    moveInfo.deltaPos.y = sinf(-PI / 2 + lpObject->elapsedTime * 2) * lpObject->speed / 2 + lpObject->speed / 2;

    return moveInfo;
}
