#include "BasicPattern.h"
#include "GameObject.h"
#include "Missile.h"

MoveInfo BasicPattern::Move(float deltaTime, GameObject* lpObject)
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

    moveInfo.angle = lpObject->angle;
	lpObject->pos.x += cosf(lpObject->angle) * lpObject->speed * deltaTime;
	lpObject->pos.y += sinf(lpObject->angle) * lpObject->speed * deltaTime;

	return moveInfo;
}
