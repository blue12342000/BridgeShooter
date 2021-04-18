#include "RainFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "RainPattern.h"
#include "BasicPattern.h"
#include <cmath>

void RainFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::RFCP_NONE);
	vLpPatterns[CREATE_PATTERN::RFCP_BASIC] =new BasicPattern();
	vLpPatterns[CREATE_PATTERN::RFCP_RAIN] = new RainPattern();
	
	maxCreateLIne = 2;
	srand(time(NULL));
}

void RainFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void RainFactory::Fire(Unit* lpUnit)
{
	rnd = rand() % 100;
	if (createLine == 0)
	{
		for (int i = 0; i < 5; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos.x = lpUnit->pos.x - (i - 2) * rnd;
			lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle + PI / 32 * (i - 2), 150, 1);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::RFCP_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
	if (createLine == 1)
	{
		if ((int)(lpUnit->elapsedTime * 10) % 3 == 0)
		{
			for (int i = -1; i < 2; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle + PI / 64 * i, 200, 3);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::RFCP_RAIN]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
			}
		}
	}
}