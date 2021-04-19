#include "SpaceShipFactory.h"
#include "BasicPattern.h"
#include "ReflectPattern.h"
#include "Missile.h"
#include "Unit.h"

void SpaceShipFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::SFCP_NONE);
	vLpPatterns[CREATE_PATTERN::SFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_REFLECT] = new ReflectPattern();

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
			lpMissile->SetMissile("MISSILE_04", lpUnit->pos, lpUnit->angle, 500, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
	else if (createLine == 1)
	{
		if (IsCheckTime(100))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_05", lpUnit->pos, lpUnit->angle, 500, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
	else if (createLine == 2)
	{
		if (IsCheckTime(100))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_05", lpUnit->pos, lpUnit->angle, 500, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);

			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_04", { lpUnit->pos.x + i * 20, lpUnit->pos.y + 10 }, lpUnit->angle, 500, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
			}
		}
	}
	else if (createLine == 3)
	{
		if (IsCheckTime(100))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_05", lpUnit->pos, lpUnit->angle, 500, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);

			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_04", { lpUnit->pos.x + i * 20, lpUnit->pos.y + 10 }, lpUnit->angle, 500, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
			}

			for (int i = -1; i < 2; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_04", { lpUnit->pos.x + i * 40, lpUnit->pos.y + 10 }, lpUnit->angle + (PI / 16) * i, 500, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
			}
		}
	}
}
