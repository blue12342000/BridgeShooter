#include "SSJFactory.h"
#include "Factory.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "Missile.h"
#include "SinePattern.h"
#include "SpiralPattern.h"
#include "ReverseSpiralPattern.h"
#include "SinePattern.h"
#include "ReflectPattern.h"
#include "DelayBasicPattern.h"
#include "BridgeShooter.h"


void SSJFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::SFCP_NONE);
	vLpPatterns[CREATE_PATTERN::SFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_SPIRAL] = new SpiralPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_REVERSE_SPIRAL] = new ReverseSpiralPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_SINE] = new SinePattern();
	vLpPatterns[CREATE_PATTERN::SFCP_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_DELAYBASIC] = new DelayBasicPattern();

	createLine = 0;
	maxCreateLIne = 3;

	phaseChanger = 0;

	SetCheckTime(100);
	SetCheckTime(200);
	SetCheckTime(300);
	SetCheckTime(1000);
	SetCheckTime(3000);
}

void SSJFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void SSJFactory::Fire(Unit* lpUnit)
{

	phaseChanger++;
	if (phaseChanger >= 3000) createLine = 1;
	if (phaseChanger >= 6000) createLine = 2;

	//1페이즈
	if (createLine == 0)
	{
		//36방향으로 원처럼 발사
		if (IsCheckTime(1000))
		{
			for (int i = 0; i < 36; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle - 2 * PI / 36 * i, 200, 14);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}

		}
		if (IsCheckTime(200))
		{
			//꽃모양 만드는 스파이럴
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle - 2 * PI / 8 * i, 300, 14);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
				
			}
			//꽃모양 만드는 역스파이럴
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle - 2 * PI / 8 * i, 300, 14);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REVERSE_SPIRAL]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}

	}
		
	//2페이즈
	else if (createLine == 1)
	{
		if (IsCheckTime(100))
		{
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle - 2 * PI / 6 * i, 500, 14);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", { lpUnit->pos.x + 300, lpUnit->pos.y + 300 }, lpUnit->angle - 2 * PI / 6 * i, 500, 14);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", { lpUnit->pos.x - 300, lpUnit->pos.y - 300 }, lpUnit->angle - 2 * PI / 6 * i, 500, 14);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", { lpUnit->pos.x - 300, lpUnit->pos.y + 300 }, lpUnit->angle - 2 * PI / 6 * i, 500, 14);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", { lpUnit->pos.x + 300, lpUnit->pos.y + 300 }, lpUnit->angle - 2 * PI / 6 * i, 500, 14);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		
		//반사 레이저
		if(IsCheckTime(200))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->pos, lpUnit->angle - 2 * PI / 5 * 4, 500, 14);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REFLECT]);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
		//반사 레이저
		else if (IsCheckTime(300))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->pos, lpUnit->angle - 2 * PI / 5 * 1, 500, 14);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REFLECT]);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
	}

	//3페이즈
	else if (createLine == 2)
	{
		if (IsCheckTime(3000))
		{
			for (int j = 0; j < 10; ++j)
			{
				for (int i = 0; i < 20; ++i)
				{
					if (patternArray[i + j * 20] == 1)
					{
						Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
						lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle - PI*4/5 - 0.05 * i, 200, 14, 0.07f*j);
						lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_DELAYBASIC]);
						lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
						MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
					}
					else
						continue;

				}

			}
		}

	}
}
