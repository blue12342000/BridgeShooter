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

	createLine = 1;
	maxCreateLIne = 3;
	SetCheckTime(1001);
	SetCheckTime(2000);
	SetCheckTime(3000);
	SetCheckTime(2);
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
	if (createLine == 1)
	{
		
		if(IsCheckTime(1001))srand(time(NULL));
		if (IsCheckTime(2))
		{
			for (int i = 0; i < 1; i++)//랜덤 미사일
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos,lpUnit->angle + (rand() % (int)(2 * PI * 1000)) / 1000.0f,300, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
	else if (createLine == 2)
	{
		if (IsCheckTime(2000)) 
		{
			for (int i = 0; i < 16; i++)// 호밍같은 부메랑 같은 미사일
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos, 2 * PI * i / 16 + (PI*i / 8.0f), 170, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BOOMERANG]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
	else if (createLine == 3)
	{
		if (IsCheckTime(2000))
		{
			for (int i = 0; i < 16; i++)// 미사일 위에서
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", { (float)WINSIZE_WIDTH * (float)i / 16+15 ,0.0f }, PI / 2.0f, 150, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		if (IsCheckTime(3000))
		{
			for (int i = 0; i < 20; i++)// 미사일 왼쪽에서
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", { 0.0f,(float)(WINSIZE_HEIGHT + 10) * (float)i / 20 }, 0.0f, 150, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			for (int i = 0; i < 20; i++)// 미사일 오른쪽에서
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", { (float)WINSIZE_WIDTH,(float)(WINSIZE_HEIGHT + 200) * (float)i / 20 }, PI, 150, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
}
