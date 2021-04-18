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
	delayTime_0 = 0;

	phaseChanger = 0;

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
	//델타 타임으로 변경 예정
	delayTime_0 += 1;

	phaseChanger++;
	if (phaseChanger >= 2000) createLine = 1;
	if (phaseChanger >= 4000) createLine = 2;

	//1페이즈
	if (createLine == 0)
	{
		//36방향으로 원처럼 발사
		if (delayTime_0 % 100 == 0)
		{
			for (int i = 0; i < 36; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle, 200, 14);
				lpMissile->angle = lpUnit->angle - 2 * PI / 36 * i;
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}

		}
		if (delayTime_0 % 30 == 0)
		{
			//꽃모양 만드는 스파이럴
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle, 300, 14);
				lpMissile->angle = lpUnit->angle - 2 * PI / 8 * i;
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
				
			}
			//꽃모양 만드는 역스파이럴
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle, 300, 14);
				lpMissile->angle = lpUnit->angle - 2 * PI / 8 * i;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REVERSE_SPIRAL]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}

	}
		
	//2페이즈
	else if (createLine == 1)
	{
		if (delayTime_0 % 30 == 0)
		{
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle, 500, 14);
				//lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle, 500, 14);
				lpMissile->pos.x = lpUnit->pos.x + 300;
				lpMissile->pos.y = lpUnit->pos.y - 300;
				lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle, 500, 14);
				lpMissile->pos.x = lpUnit->pos.x - 300;
				lpMissile->pos.y = lpUnit->pos.y - 300;
				lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle, 500, 14);
				lpMissile->pos.x = lpUnit->pos.x - 300;
				lpMissile->pos.y = lpUnit->pos.y + 300;
				lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle, 500, 14);
				lpMissile->pos.x = lpUnit->pos.x + 300;
				lpMissile->pos.y = lpUnit->pos.y + 300;
				lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		
		//반사 레이저
		if(delayTime_0 % 51 == 0)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->pos, lpUnit->angle, 500, 14);
			lpMissile->angle = lpUnit->angle - 2 * PI / 5*4;
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REFLECT]);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
		//반사 레이저
		else if (delayTime_0 % 71 == 0)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->pos, lpUnit->angle, 500, 14);
			lpMissile->angle = lpUnit->angle - 2 * PI / 5 * 1;
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REFLECT]);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
	}

	//3페이즈
	else if (createLine == 2)
	{
		if (delayTime_0 % 2000 == 0)
		{
			for (int j = 0; j < 10; ++j)
			{
				for (int i = 0; i < 20; ++i)
				{
					if (patternArray[i + j * 20] == 1)
					{
						Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
						lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle, 200, 14);
						lpMissile->angle = lpUnit->angle - PI*4/5 - 0.05 * i;
						lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_DELAYBASIC]);
						lpMissile->SetDelayTime(0.07f * j);
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
