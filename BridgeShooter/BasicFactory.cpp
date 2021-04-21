#include "BasicFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "SinePattern.h"
#include "BoomerangPattern.h"
#include "SpiralPattern.h"
#include "ReflectPattern.h"

void BasicFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::BFCP_NONE);
	vLpPatterns[CREATE_PATTERN::BFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::BFCP_REFLECT] = new ReflectPattern();

	maxCreateLIne = 3;
}

void BasicFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void BasicFactory::Fire(Unit* lpUnit)
{
	if (createLine == 1)
	{
		// ±‚∫ª≈∫
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile("MISSILE_01", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 200 }, 20);
		lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_BASIC]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
	else if (createLine == 2)
	{
		// ªÍ≈∫
		for (int i = 0; i < 20; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_01", lpUnit->angle + ((float)(rand() % 101) - 50) / 100, Transform{ lpUnit->pos, lpUnit->angle + ((float)(rand() % 101) - 50) / 100, rand() % 100 + 100.0f }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
	else if (createLine == 3)
	{
		// π›ªÁ
		for (int i = -3; i < 4; i += 2)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_07", lpUnit->angle + PI / 24 * i, Transform{ lpUnit->pos, lpUnit->angle + PI / 24 * i, 400 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_REFLECT]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
}
