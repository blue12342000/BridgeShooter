#include "SprialPattern.h"
#include "GameObject.h"

MoveInfo SprialPattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveInfo = {};

    //                                          ��Ÿ                                     ������     
    moveInfo.deltaPos.x = cosf(lpObject->angle + sqrt(lpObject->elapsedTime)) * lpObject->elapsedTime * lpObject->speed;
    moveInfo.deltaPos.y = sinf(lpObject->angle + sqrt(lpObject->elapsedTime)) * lpObject->elapsedTime * lpObject->speed;

    return moveInfo;
}
