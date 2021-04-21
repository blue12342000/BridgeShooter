#include "BasicPattern.h"
#include "GameObject.h"
#include "Missile.h"

void BasicPattern::Move(float deltaTime, GameObject* lpObject)
{
    Transform& transform = lpObject->transform;
    if (typeid(*lpObject) == typeid(Missile))
    {
        Missile* lpMissile = (Missile*)lpObject;
        if (lpMissile->delayTime > 0.000001f)
        {
            lpMissile->delayTime -= deltaTime;
            return;
        }
    }

	lpObject->pos.x += cosf(lpObject->angle) * transform.speed * deltaTime;
	lpObject->pos.y += sinf(lpObject->angle) * transform.speed * deltaTime;
}
