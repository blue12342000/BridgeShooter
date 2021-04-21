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
		
		if(IsCheckTime(1001))srand(time(NULL));
		if (IsCheckTime(10))
		{
			for (int i = 0; i < 1; i++)//���� �̻���
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos,lpUnit->angle + (rand() % (int)(2 * PI * 1000)) / 1000.0f,300, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
	else if (createLine == 1)
	{
		if (IsCheckTime(1000)) 
		{
			for (int i = 0; i < 16; i++)// ȣ�ְ��� �θ޶� ���� �̻���
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos, 2 * PI * i / 16 + (PI*i / 8.0f), 170, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BOOMERANG]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
	else if (createLine == 2)
	{
		if (IsCheckTime(4000))
		{
			for (int i = 0; i < 8; i++)// �̻��� ������
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", { (float)WINSIZE_WIDTH * (float)i / 8+15 ,0.0f }, PI / 2.0f, 150, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		if (IsCheckTime(3400))
		{
			for (int i = 0; i < 12; i++)// �̻��� ���ʿ���
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", { 0.0f,(float)(WINSIZE_HEIGHT + 10) * (float)i / 12 }, 0.0f, 150, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			for (int i = 0; i < 12; i++)// �̻��� �����ʿ���
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", { (float)WINSIZE_WIDTH,(float)(WINSIZE_HEIGHT + 200) * (float)i / 12 }, PI, 150, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::KFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
}
