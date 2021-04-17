#include "BasicFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "SinePattern.h"

void BasicFactory::Init()
{
	pattern = new SinePattern();
}

void BasicFactory::Fire(Unit* lpUnit)
{
	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	lpMissile->pos = lpUnit->pos;
	lpMissile->angle = lpUnit->angle;
	lpMissile->speed = 400;
	lpMissile->elapsedTime = 0;
	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	lpMissile->SetPattern(pattern);
	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);

}
