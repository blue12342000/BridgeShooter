#include "JinHwangFactory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "ReflectPattern.h"
#include "SpiralPattern.h"
#include "ReverseSpiralPattern.h"
#include "BoomerangPattern.h"
#include "Missile.h"
#include "Unit.h"

void JinHwangFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::JFCP_NONE);
	vLpPatterns[CREATE_PATTERN::JFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_SPIRAL] = new SpiralPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_REVERSE_SPIRAL] = new ReverseSpiralPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_BOOMERANG] = new BoomerangPattern();

	createLine = 2;
	maxCreateLIne = 3;

	// 1√  1000 
	SetCheckTime(100);
	SetCheckTime(200);
	SetCheckTime(300);
}

void JinHwangFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void JinHwangFactory::Fire(Unit* lpUnit)
{
	if (createLine == 0)
	{
		if (IsCheckTime(100) && GetTimeMod(10000) < 5000)
		{
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpMissile->deltaMove.deltaPos, lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i, 300, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		else if (IsCheckTime(100) && GetTimeMod(10000) >= 5000)
		{
			for (int i = 0; i < 16; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpMissile->deltaMove.deltaPos, lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 8 * i, 200, 20, i * 0.1f);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
	else if (createLine == 1)
	{
		if (IsCheckTime(200) && GetTimeMod(10000) < 5000)
		{
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpMissile->deltaMove.deltaPos, lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i, 100, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		else if (IsCheckTime(200))
		{
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpMissile->deltaMove.deltaPos, lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i, 100, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_REVERSE_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}

		if (IsCheckTime(200))
		{
			for (int i = -1; i < 2; i += 2)
			{
				for (int l = 0; l < 6; ++l)
				{
					Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
					lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpMissile->deltaMove.deltaPos, lpUnit->angle + PI * 2 / 5 * i, 400, 20, 0.02f * i);
					lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_REFLECT]);
					MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
				}
			}
		}
	}
	else if (createLine == 2)
	{
		if (IsCheckTime(300) && GetTimeMod(10000) < 5000)
		{
			float splitY = WINSIZE_HEIGHT / 8;
			for (float y = 0; y <= WINSIZE_HEIGHT; y += splitY)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", { 0, y }, { 0,0 }, 0, 300, 20, 0.1f * (int)(y / splitY));
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}

			for (float y = WINSIZE_HEIGHT + splitY / 2; y >= 0; y -= splitY)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", { WINSIZE_WIDTH, y }, { 0,0 }, PI, 300, 20, 0.1f * (int)(y / splitY));
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
}
