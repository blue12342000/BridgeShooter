#include "BoomerangPattern.h"
#include "GameObject.h"
#include "Missile.h"

void BoomerangPattern::Move(float deltaTime, GameObject* lpObject)
{
    if (lpObject)
    {
        Transform& transform = lpObject->transform;
        if (typeid(*lpObject)== typeid(Missile))
        {
            Missile* lpMissile = (Missile*)lpObject;

            if ((lpObject->pos.x <= 0) || (lpObject->pos.x >= WINSIZE_WIDTH)
                || (lpObject->pos.y <= 0) || (lpObject->pos.y >= WINSIZE_HEIGHT))
            {
                lpMissile->elapsedTime = 0;
                lpMissile->SetDelayTime(stopTime);
                lpMissile->SetPattern(&guideBasicPattern);
            }
            else
            {
                lpObject->pos.x += cos(transform.angle) * transform.speed * deltaTime;
                lpObject->pos.y += sin(transform.angle) * transform.speed * deltaTime;
            }
        }
    }
}
