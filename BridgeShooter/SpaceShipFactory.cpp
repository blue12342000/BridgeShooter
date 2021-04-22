#include "SpaceShipFactory.h"
#include "BasicPattern.h"
#include "ReflectPattern.h"
#include "Missile.h"
#include "Unit.h"
#include "GuidePattern.h"

void SpaceShipFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::SFCP_NONE);
	vLpPatterns[CREATE_PATTERN::SFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_GUIDE] = new GuidePattern();

	createLine = 0;
	maxCreateLIne = 4;

	SetCheckTime(100);
}

void SpaceShipFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void SpaceShipFactory::Fire(Unit* lpUnit)
{
	if (createLine == 0)
	{
		if (IsCheckTime(100))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_04", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 500 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
			lpMissile->SetLpTarget(&lpUnit->GetTarget());
			lpMissile->SetDamage(2);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
		}
	}
	else if (createLine == 1)
	{
		if (IsCheckTime(100))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_05", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 500 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
			lpMissile->SetDamage(3);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
		}
	}
	else if (createLine == 2)
	{
		if (IsCheckTime(100))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_05", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 500 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
			lpMissile->SetDamage(3);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);

			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_04", lpUnit->angle, Transform{ { lpUnit->pos.x + i * 20, lpUnit->pos.y + 10 }, lpUnit->angle, 500 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
				lpMissile->SetDamage(1);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
	else if (createLine == 3)
	{
		if (IsCheckTime(100))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_05", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 500 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
			lpMissile->SetDamage(3);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);

			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_04", lpUnit->angle, Transform{ { lpUnit->pos.x + i * 20, lpUnit->pos.y + 10 }, lpUnit->angle, 500 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
				lpMissile->SetDamage(2);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}

			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_09", lpUnit->angle + (PI / 16) * i, Transform{ { lpUnit->pos.x + i * 20, lpUnit->pos.y + 10 }, lpUnit->angle + (PI / 16) * i, 500 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_GUIDE]);
				lpMissile->SetLpTarget(&lpUnit->GetTarget());
				lpMissile->SetDamage(1);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
}
