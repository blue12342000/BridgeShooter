#include "BridgeShooter.h"
#include "SineFactory.h"
#include "SinePattern.h"
#include "Missile.h"
#include "Unit.h"
#include "SpiralPattern.h"
#include "BasicPattern.h"
#include "ReflectPattern.h"

void SineFactory::Init()
{
	vLpPatterns.resize(SFCP_NONE);
	vLpPatterns[SFCP_SINE] = new SinePattern();
	vLpPatterns[SFCP_BASIC] = new BasicPattern();
	vLpPatterns[SFCP_REFLECT] = new ReflectPattern();

	maxCreateLIne = 4;
	SetCheckTime(100);
	SetCheckTime(400);
}

void SineFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void SineFactory::Fire(Unit* lpUnit)
{
	if (IsCheckTime(100))
	{
		for (int i = -1; i < 2; i += 2)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_04", lpUnit->angle, Transform{ lpUnit->pos, PI / 2 * i, 500, PI * 8, 30 }, 20);
			lpMissile->SetPattern(vLpPatterns[SFCP_SINE]);
			lpMissile->SetDamage(1 + createLine / 2);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
		}
	}
	if (createLine == 1)
	{
		if (IsCheckTime(400))
		{
			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_09", lpUnit->angle + PI / 8 * i, Transform{ lpUnit->pos, lpUnit->angle + PI / 8 * i, 300 }, 20);
				lpMissile->SetPattern(vLpPatterns[SFCP_REFLECT]);
				lpMissile->SetDamage(2);
				lpMissile->elapsedTime = 10;
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
	else if (createLine == 2)
	{
		if (IsCheckTime(300))
		{
			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_09", lpUnit->angle + PI / 8 * i, Transform{ lpUnit->pos, lpUnit->angle + PI / 8 * i, 500 }, 20);
				lpMissile->SetPattern(vLpPatterns[SFCP_REFLECT]);
				lpMissile->SetDamage(2);
				lpMissile->elapsedTime = 8.5f;
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
	else if (createLine == 3)
	{
		if (IsCheckTime(200))
		{
			for (int i = -3; i < 4; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_09", lpUnit->angle + PI / 16 * i, Transform{ lpUnit->pos, lpUnit->angle + PI / 16 * i, 500 }, 20);
				lpMissile->SetPattern(vLpPatterns[SFCP_REFLECT]);
				lpMissile->SetDamage(2);
				lpMissile->elapsedTime = 8.5f;
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
}
