#include "Planet04Factory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "RainPattern.h"
#include "BasicPattern.h"

void Planet04Factory::Init()
{
	pattern = new RainPattern();
	pattern2 = new BasicPattern();
	count = -9;
}

void Planet04Factory::Fire(Unit* lpObject)
{
	++count;
	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	lpMissile->pos = lpObject->pos;
	lpMissile->angle = lpObject->angle += PI * count / 16;
	lpMissile->speed = 200;
	lpMissile->elapsedTime = 0;
	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	lpMissile->lpPattern = pattern;
	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	if (count >= 9) count *= -1;



	if ((int)(lpObject->elapsedTime * 10) % 3 == 0)
	{
		for (int i = -1; i < 2; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpObject->pos;
			lpMissile->angle = lpObject->angle - PI / 64 * i;
			lpMissile->speed = 200;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->lpPattern = pattern2;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
}