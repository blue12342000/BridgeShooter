#include "Planet04Factory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "RainPattern.h"
#include "ReflectPattern.h"
#include "SpiralPattern.h"
#include "Missile.h"
#include "Unit.h"
//#include "Factory.h"

void Planet04Factory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::PLANET04_NONE);
	vLpPatterns[CREATE_PATTERN::PLANET04_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_RAIN] = new RainPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_SPRIAL] = new SpiralPattern();
	
	createLine = 0;
	maxCreateLIne = 3;


	// 1ch 1000
	SetCheckTime(10);
	SetCheckTime(50);
	SetCheckTime(100);
	SetCheckTime(200);
	SetCheckTime(300);
	SetCheckTime(500);
	SetCheckTime(1000);
}

void Planet04Factory::Release()
{
	//자동으로 타입 적게해줌 auto. 싱기방기
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void Planet04Factory::Fire(Unit* lpUnit)
{
	//체력에 맞게 조절이 필요
	
	if (createLine == 0)
	{
		if (IsCheckTime(100) && GetTimeMod(100) < 1000)
		{

			for (int i = 0; i < 4; ++i)	//한번에 여러개 나가게 하기
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpUnit->angle -= lpUnit->elapsedTime * (PI / 64 * i);
				lpMissile->SetMissile("MISSILE_03", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 400 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
	
	//2페이즈
	if (createLine == 1)
	{
		if (IsCheckTime(300) && GetTimeMod(10000) < 5000)
		{
			++count;
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			//lpMissile->angle = PI / 2;
			lpUnit->angle += PI * count / 16;
			lpMissile->SetMissile("MISSILE_01", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 150 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_RAIN]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			if (count >= 9) count *= -1;
		}
	
		if (IsCheckTime(100) && GetTimeMod(10000) < 5000)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpUnit->angle += -PI / 32;
			lpMissile->SetMissile("MISSILE_02", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 200 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_SPRIAL]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
		if (IsCheckTime(100) && GetTimeMod(10000) < 5000)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpUnit->angle += -PI / 32;
			lpMissile->SetMissile("MISSILE_02", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 200 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_SPRIAL]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
	}

	//3페이즈

	if (createLine == 2)
	{
		if (IsCheckTime(50) && GetTimeMod(10000) < 5000)
		{
			++count;
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpUnit->angle += PI * count / 16;
			lpMissile->SetMissile("MISSILE_01", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 150 + (8 * count) }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_RAIN]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			if (count >= 9) count *= -1;
		}

		if (IsCheckTime(50) && GetTimeMod(10000) < 5000)
		{
			for (int i = -3; i < 4; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->angle - PI / 64 * i, Transform{ lpUnit->pos, lpUnit->angle - PI / 64 * i, 200 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
}