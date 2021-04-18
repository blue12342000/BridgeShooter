#include "DelayBasicPattern.h"
#include "GameObject.h"
#include "Missile.h"

MoveInfo DelayBasicPattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveInfo = { 0, 0 };

    
    if (typeid(*lpObject) == typeid(Missile))
    {
        Missile* lpMissile = (Missile*)lpObject;
        lpMissile->delayTime -= deltaTime;
        if (lpMissile->delayTime < 0.001f)
        {
            lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
            lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;
        }
        

    }

    return moveInfo;
}
