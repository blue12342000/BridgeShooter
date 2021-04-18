#include "BoomerangPattern.h"
#include "GameObject.h"
#include"Missile.h"
MoveInfo BoomerangPattern::Move(float deltaTime, GameObject* lpObject)
{
    MoveInfo moveinfo = {};
    if (lpObject)
    {
       
        if (typeid(*lpObject)== typeid(Missile))
        {
            Missile* lpMissile = (Missile*)lpObject;
            if ((lpObject->elapsedTime>=0.000f)&& (lpObject->elapsedTime <= 0.01f)) {
                lpMissile->SetDelayTime(-10);//-·Î
            }
            
            if (lpMissile->delayTime >= 0.001f) 
            {
                lpMissile->delayTime -= deltaTime;
                
                    lpObject->angle = atan2((WINSIZE_HEIGHT / 2) -lpObject->pos.y , (WINSIZE_WIDTH / 2)-lpObject->pos.x  );
                
            }
            if (lpMissile->delayTime < 0.001f)
            {
                lpObject->pos.x += cos(lpObject->angle) * lpObject->speed * deltaTime;
                lpObject->pos.y += sin(lpObject->angle) * lpObject->speed * deltaTime;
            }
            if (((lpMissile->delayTime < -1.0f)) && ((lpObject->pos.x <= 0) || (lpObject->pos.x >= WINSIZE_WIDTH) || (lpObject->pos.y <= 0) || (lpObject->pos.y >= WINSIZE_HEIGHT))) {
                lpMissile->delayTime = stopTime;
            }
           
        }
       
       
    }
    return moveinfo;
}
