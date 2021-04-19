#include "Planet04Factory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "RainPattern.h"
#include "ReflectPattern.h"
#include "SpiralPattern.h"
#include "Missile.h"
#include "Unit.h"
#include "Factory.h"

void Planet04Factory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::PLANET04_NONE);
	vLpPatterns[CREATE_PATTERN::PLANET04_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_RAIN] = new RainPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_SPRIAL] = new SpiralPattern();
	
	createLine = 0;
	maxCreateLIne = 3;
	bossCount = 0;

	SetCheckTime(30);
	SetCheckTime(50);

	SetCheckTime(100);
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
	//��Ÿ Ÿ������ ���� ����

	bossCount++;
	if (bossCount >= 10000) createLine = 1;
	if (bossCount >= 12500) createLine = 2;
	//1������
	if (createLine == 0)
	{
		if (IsCheckTime(30) && GetTimeMod(100) < 10000)
		{
			for (int i = -1; i < 2; ++i)	//�ѹ��� ������ ������ �ϱ�
			{
				count -= 2;
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle - (PI / 16*i)-(count+bossCount);
				lpMissile->speed = 200;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
				if (count % 400 <= 200)
				{
					count = 0;
				}
			}
		
		}
	}

	//2������
	if (createLine == 1)
	{
		++count;
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = lpUnit->pos;
		lpMissile->angle = PI / 2;
		lpMissile->angle = lpUnit->angle += PI * count / 16;
		lpMissile->speed = 150;
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->deltaMove.deltaPos = { 0,  0 };
		lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_RAIN]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		if (count >= 9) count *= -1;
	
		if (IsCheckTime(30) && GetTimeMod(10000) < 5000)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - PI / 32;
			lpMissile->speed = 200;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
	}

	//3������

	if (createLine == 2)
	{
		++count;
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = lpUnit->pos;
		lpMissile->angle = PI / 2;
		lpMissile->angle = lpUnit->angle += PI * count / 16;
		lpMissile->speed = 150 + (8*count);
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->deltaMove.deltaPos = { 0,  0 };
		lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_RAIN]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		if (count >= 9) count *= -1;


		if (IsCheckTime(30) && GetTimeMod(10000) < 5000)
		{
			for (int i = -1; i < 2; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle - PI / 64 * i;
				lpMissile->speed = 200;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
}