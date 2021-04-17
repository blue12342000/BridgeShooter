#include "SSJFactory.h"
#include "Factory.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "Missile.h"

void SSJFactory::Init()
{
	pattern1 = new BasicPattern();
}

void SSJFactory::Release()
{
	if (pattern1) delete pattern1; pattern1 = nullptr;
}

void SSJFactory::Fire(Unit* lpUnit)
{
	if ((int)lpUnit->elapsedTime %3 == 0)
	{
		for (int i = -2; i < 3; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 0.1f * i -PI;
			lpMissile->speed = 200;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern1);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
	
	else if ((int)lpUnit->elapsedTime %3 == 1)
	{
		for (int i = -2; i < 3; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 0.1f * i - PI - 0.8f;
			lpMissile->speed = 200;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern1);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
	else
	{
		for (int i = -2; i < 3; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 0.1f * i - PI +0.8f;
			lpMissile->speed = 200;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern1);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}

}
