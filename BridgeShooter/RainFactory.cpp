#include "BridgeShooter.h"
#include "RainFactory.h"
#include "RainPattern.h"
#include "Missile.h"
#include "Unit.h"

void RainFactory::Init()
{
	pattern = new RainPattern();
}

void RainFactory::Fire(Unit* lpObject)
{
	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	lpMissile->pos = lpObject->pos;
	lpMissile->angle = lpObject->angle;
	lpMissile->speed = 150;
	lpMissile->elapsedTime = 0;
	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	lpMissile->lpPattern = pattern;
	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
}
