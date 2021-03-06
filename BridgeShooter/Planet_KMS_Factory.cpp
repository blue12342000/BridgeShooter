#include "Planet_KMS_Factory.h"
#include "Pattern.h"
#include"BoomerangPattern.h"
#include"BasicPattern.h"
#include "Unit.h"
#include"Missile.h"
#include<ctime>

void Planet_KMS_Factory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::KFCP_NONE);
	vLpPatterns[CREATE_PATTERN::KFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::KFCP_BOOMERANG] = new BoomerangPattern();

	createLine = 0;
	maxCreateLIne = 3;
	SetCheckTime(1001);
	SetCheckTime(3400);
	SetCheckTime(4000);
	SetCheckTime(1000);
	SetCheckTime(10);
}	



void Planet_KMS_Factory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void Planet_KMS_Factory::Fire(Unit* lpUnit)
{
	if (createLine == 0)
	{
		if (IsCheckTime(10))
		{
			for (int i = 0; i < 1; i++)//랜덤 미사일
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->angle + (rand() % (int)(2 * PI * 1000)) / 1000.0f, Transform{ lpUnit->pos, lpUnit->angle + (rand() % (int)(2 * PI * 1000)) / 1000.0f, 300 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
	else if (createLine == 1)
	{
		if (IsCheckTime(1000)) 
		{
			for (int i = 0; i < 16; i++)// 호밍같은 부메랑 같은 미사일
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", 2 * PI * i / 16 + (PI * i / 8.0f), Transform{ lpUnit->pos, 2 * PI * i / 16 + (PI * i / 8.0f), 170 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BOOMERANG]);
				lpMissile->SetLpTarget(&lpUnit->GetTarget());
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
	else if (createLine == 2)
	{
		if (IsCheckTime(4000))
		{
			for (int i = 0; i < 10; i++)// 미사일 위에서
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", PI / 2.0f, Transform{ { (float)WINSIZE_WIDTH * (float)i / 10+50  ,0.0f }, PI / 2.0f, 150 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
		if (IsCheckTime(3400))
		{
			for (int i = 0; i < 12; i++)// 미사일 왼쪽에서
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", 0, Transform{ { 0.0f,(float)(WINSIZE_HEIGHT + 630) * (float)i / 20 }, 0.0f, 150 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
			for (int i = 0; i < 12; i++)// 미사일 오른쪽에서
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", PI, Transform{ { (float)WINSIZE_WIDTH,(float)(WINSIZE_HEIGHT + 700) * (float)i / 20 }, PI, 150 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
	}
}
