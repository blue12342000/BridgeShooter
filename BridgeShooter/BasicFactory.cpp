#include "BasicFactory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "Missile.h"

BasicFactory::BasicFactory()
{
	pattern = new BasicPattern();
}

BasicFactory::~BasicFactory()
{
	if (pattern) delete pattern;
}

void BasicFactory::Fire(GameObject* lpObject)
{
	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	lpMissile->pos = lpObject->pos;
	lpMissile->angle = lpObject->angle;
	lpMissile->speed = 300;
	lpMissile->elapsedTime = 0;
	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	lpMissile->lpPattern = pattern;
	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
}
