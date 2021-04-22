#include "RainFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "RainPattern.h"

#include <cmath>

void RainFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::RFCP_NONE);
	vLpPatterns[CREATE_PATTERN::RFCP_BASIC] =new BasicPattern();
	vMissileKey.resize(3);
	vMissileKey[0] = "MISSILE_04";
	vMissileKey[1] = "MISSILE_04";
	vMissileKey[2] = "MISSILE_10";

	maxCreateLIne = 4;
	missileCount = 0;

	SetCheckTime(150);
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
	if (IsCheckTime(150))
	{

		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile(vMissileKey[missileCount], lpUnit->angle, Transform{ {lpUnit->pos.x + cosf(lpUnit->angle) * 25, lpUnit->pos.y + sinf(lpUnit->angle) * 25}, lpUnit->angle, 500 }, 20);
		lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::RFCP_BASIC]);
		if (missileCount == 2) lpMissile->SetDamage(2);
		MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);

		for (int i = -1; i < 2; i += 2)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile(vMissileKey[missileCount], lpUnit->angle, Transform{ {lpUnit->pos.x + cosf(lpUnit->angle) * 20 + 10 * i, lpUnit->pos.y + sinf(lpUnit->angle) * 20}, lpUnit->angle, 500 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::RFCP_BASIC]);
			if (missileCount == 2) lpMissile->SetDamage(2);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
		}

		if (createLine > 0)
		{
			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile(vMissileKey[missileCount], lpUnit->angle, Transform{ {lpUnit->pos.x + cosf(lpUnit->angle) * 10 + 15 * i, lpUnit->pos.y + sinf(lpUnit->angle) * 10}, lpUnit->angle, 500 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::RFCP_BASIC]);
				if (missileCount == 2) lpMissile->SetDamage(2);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
		if (createLine > 1)
		{
			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile(vMissileKey[missileCount], lpUnit->angle, Transform{ {lpUnit->pos.x + 20 * i, lpUnit->pos.y}, lpUnit->angle, 500 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::RFCP_BASIC]);
				if (missileCount == 2) lpMissile->SetDamage(2);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
		if (createLine > 2)
		{
			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile(vMissileKey[missileCount], lpUnit->angle, Transform{ {lpUnit->pos.x - cosf(lpUnit->angle) * 10 + 20 * i, lpUnit->pos.y - sinf(lpUnit->angle) * 10}, lpUnit->angle, 500 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::RFCP_BASIC]);
				if (missileCount == 2) lpMissile->SetDamage(2);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
		missileCount = ++missileCount % 3;
	}
}