#include "BoomerangPattern.h"
#include "GameObject.h"
MoveInfo BoomerangPattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveinfo = {};
    if (lpObject)
    {


        if (((lpObject->elapsedTime > stopTime + stopDuration) && (lpObject->elapsedTime <= stopTime + stopDuration + 0.01f)))
        {
            lpObject->angle = atan2((WINSIZE_HEIGHT / 2) - lpObject->pos.y, (WINSIZE_WIDTH / 2) - lpObject->pos.x);
        }
        if (!(((lpObject->elapsedTime > stopTime) && (lpObject->elapsedTime <= stopTime + stopDuration)) ||
            ((lpObject->elapsedTime <= stopTime)) && ((lpObject->pos.x <= 0) ||(lpObject->pos.x >= WINSIZE_WIDTH) || (lpObject->pos.y <= 0) || (lpObject->pos.y >= WINSIZE_HEIGHT)))) {
            lpObject->pos.x += cos(lpObject->angle) * lpObject->speed * deltaTime;
            lpObject->pos.y += sin(lpObject->angle) * lpObject->speed * deltaTime;
        }



    }
    return moveinfo;
}
