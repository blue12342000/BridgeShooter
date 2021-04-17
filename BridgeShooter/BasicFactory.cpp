#include "BasicFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "SinePattern.h"

void BasicFactory::Init()
{
	pattern = new BasicPattern();
}

void BasicFactory::Fire(Unit* lpUnit)
{
	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	lpMissile->pos = lpUnit->pos;
	lpMissile->angle = lpUnit->angle;
	lpMissile->speed = 300;
	lpMissile->elapsedTime = 0;
	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	lpMissile->lpPattern = pattern;
	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);

}
