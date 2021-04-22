#include "Planet04Factory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "RainPattern.h"
#include "ReflectPattern.h"
#include "SinePattern.h"
#include "Missile.h"
#include "Unit.h"
//#include "Factory.h"

void Planet04Factory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::PLANET04_NONE);
	vLpPatterns[CREATE_PATTERN::PLANET04_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_RAIN] = new RainPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_SINE] = new SinePattern();
	
	createLine = 0;
	maxCreateLIne = 3;


	// 1ch 1000
	SetCheckTime(10);
	SetCheckTime(30);
	SetCheckTime(50);
	SetCheckTime(100);
	SetCheckTime(200);
	SetCheckTime(300);
	SetCheckTime(500);
	SetCheckTime(1000);
}

void Planet04Factory::Release()
{
	//�ڵ����� Ÿ�� �������� auto. �̱���
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void Planet04Factory::Fire(Unit* lpUnit)
{
	//ü�¿� �°� ������ �ʿ�
	
	if (createLine == 0)
	{
		if (IsCheckTime(100) && GetTimeMod(100) < 100)
		{

			for (int i = 0; i < 4; ++i)	//�ѹ��� ������ ������ �ϱ�
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpUnit->angle -= lpUnit->elapsedTime * (PI / 64 * i);
				lpMissile->SetMissile("MISSILE_03", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 400 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
	
	//2������
	if (createLine == 1)
	{
		if (IsCheckTime(300) && GetTimeMod(10000) < 10000)
		{
			++count;
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			//lpMissile->angle = PI / 2;
			lpUnit->angle += PI * count / 16;
			lpMissile->SetMissile("MISSILE_01", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle, 150 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_RAIN]);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			if (count >= 9) count *= -1;
		}
	
		if (IsCheckTime(50) && GetTimeMod(1000) < 1000)
		{
			for (int i = 0; i < 9; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->angle - 2 * PI / 9 * i, Transform{ lpUnit->pos, -PI / 2, 300, PI, 100 }, 14, 0);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_SINE]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
		if (IsCheckTime(50) && GetTimeMod(1000) < 1000)
		{
			for (int i = 0; i < 9; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->angle - 2 * PI / 9 * i, Transform{ lpUnit->pos, PI / 2, 300, PI, 100 }, 14, 0);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_SINE]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}

	//3������

	if (createLine == 2)
	{
		if (IsCheckTime(30) && GetTimeMod(15000) < 15000)
		{
			++count;
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_01", lpUnit->angle, Transform{ lpUnit->pos, lpUnit->angle += PI * count / 16, 150.0f + (8 * count) }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_RAIN]);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			if (count >= 9) count *= -1;
		}

		if (IsCheckTime(50) && GetTimeMod(10000) < 8000)
		{
			for (int i = -2; i < 3; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->angle - PI / 64 * i, Transform{ lpUnit->pos, lpUnit->angle - PI / 64 * i, 200 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
}