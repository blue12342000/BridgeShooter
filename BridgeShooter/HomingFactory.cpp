#include "BridgeShooter.h"
#include "HomingFactory.h"
#include "HomingPattern.h"
#include "Missile.h"
#include "Unit.h"

void HomingFactory::Init()
{
	pattern = new HomingPattern();
}

void HomingFactory::Fire(Unit* lpObject)
{
	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	lpMissile->pos = lpObject->pos;
	lpMissile->angle = lpObject->angle;
	lpMissile->speed = 100;
	lpMissile->elapsedTime = 0;
	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	lpMissile->lpPattern = pattern;
	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
}
