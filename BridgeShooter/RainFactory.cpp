#include "RainFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "RainPattern.h"
#include "BasicPattern.h"
#include <cmath>

void RainFactory::Init()
{
	lpPattern01 = new RainPattern();
	lpPattern02 = new BasicPattern();
	srand(time(NULL));
}

void RainFactory::Fire(Unit* lpObject)
{
	rnd = rand() % 100;
	if ((int)(lpObject->elapsedTime * 10) % 2 == 0)
	{
		for (int i = 0; i < 5; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpObject->pos;
			lpMissile->pos.x = lpObject->pos.x - (i - 2) * rnd;
			lpMissile->angle = lpObject->angle + PI / 32 * (i - 2);
			lpMissile->speed = 150;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
			lpMissile->lpPattern = lpPattern01;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}

	if ((int)(lpObject->elapsedTime * 10) % 3 == 0)
	{
		for (int i = -1; i < 2; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpObject->pos;
			lpMissile->angle = lpObject->angle + PI / 64 * i;
			lpMissile->speed = 200;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->lpPattern = lpPattern02;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
}