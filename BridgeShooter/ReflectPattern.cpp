#include "ReflectPattern.h"
#include "GameObject.h"
#include "Missile.h"

MoveInfo ReflectPattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveInfo = { 0, 0 };

    if (typeid(*lpObject) == typeid(Missile))
    {
        Missile* lpMissile = (Missile*)lpObject;
        if (lpMissile->delayTime > 0.000001f)
        {
            lpMissile->delayTime -= deltaTime;
            return moveInfo;
        }
    }

    lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
    lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;

    while (lpObject->angle > PI * 2) lpObject->angle -= PI * 2;
    while (lpObject->angle < 0) lpObject->angle += PI * 2;

    if (lpObject->elapsedTime < 10)
    {
        if (lpObject->pos.x < 0)
        {
            lpObject->pos.x = 0;
            if (lpObject->angle > PI)
            {
                lpObject->angle = PI * 3 - lpObject->angle;
            }
            else
            {
                lpObject->angle = PI - lpObject->angle;
            }
        }
        else if (lpObject->pos.x > WINSIZE_WIDTH)
        {
            lpObject->pos.x = WINSIZE_WIDTH;
            if (lpObject->angle > PI)
            {
                lpObject->angle = 3 * PI - lpObject->angle;
            }
            else
            {
                lpObject->angle = PI - lpObject->angle;
            }
        }
        
        if (lpObject->pos.y < 0)
        {
            lpObject->pos.y = 0;
            lpObject->angle = PI * 2 - lpObject->angle;
        }
        else if (lpObject->pos.y > WINSIZE_HEIGHT)
        {
            lpObject->pos.y = WINSIZE_HEIGHT;
            if (lpObject->angle > PI / 2)
            {
                lpObject->angle = PI * 2 - lpObject->angle;
            }
            else
            {
                lpObject->angle = -lpObject->angle;
            }
        }
    }
    moveInfo.angle = lpObject->angle;
    return moveInfo;
}
