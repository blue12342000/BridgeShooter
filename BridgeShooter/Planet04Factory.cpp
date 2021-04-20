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
	SetCheckTime(30);
	SetCheckTime(50);

	SetCheckTime(100);
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
		if (IsCheckTime(30) && GetTimeMod(100) < 1000)

		for (int i = 0; i < 4; ++i)	//한번에 여러개 나가게 하기
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->pos, lpUnit->angle -= lpUnit->elapsedTime * (PI / 64 * i), 500, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
	}
	
	//2페이즈
	if (createLine == 1)
	{
		++count;
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->angle = PI / 2;
		lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle += PI * count / 16 , 150, 20);
		lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_RAIN]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		if (count >= 9) count *= -1;
	
		if (IsCheckTime(30) && GetTimeMod(10000) < 5000)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle += - PI / 32, 200, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
	}

	//3페이즈

	if (createLine == 2)
	{
		++count;
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->angle = PI / 2;
		lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle += PI * count / 16, 150 + (8 * count), 20);
		lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_RAIN]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		if (count >= 9) count *= -1;


		if (IsCheckTime(30) && GetTimeMod(10000) < 5000)
		{
			for (int i = -1; i < 2; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle - PI / 64 * i, 200, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
}