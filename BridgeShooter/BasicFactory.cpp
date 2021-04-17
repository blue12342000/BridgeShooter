#include "BasicFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "SinePattern.h"
#include "BoomerangPattern.h"
#include "SprialPattern.h"

void BasicFactory::Init()
{
	pattern = new SprialPattern();
	pattern2 = new BasicPattern();
}

void BasicFactory::Fire(Unit* lpUnit)
{
	for (int i = 0; i < 16; ++i)
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = lpUnit->pos;
		lpMissile->angle = lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 8 * i;
		lpMissile->speed = 100;
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->deltaMove.deltaPos = { 0,  0 };
		lpMissile->SetPattern(pattern);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}

	for (int i = -3; i < 4; ++i)
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = lpUnit->pos;
		lpMissile->angle = lpUnit->angle + PI / 16 * i;
		lpMissile->speed = 300;
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
		lpMissile->deltaMove.deltaPos = { 0,  0 };
		lpMissile->SetPattern(pattern2);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}
