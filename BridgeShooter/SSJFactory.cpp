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

	//1??????
	if (createLine == 0)
	{
		//36???????? ????? ???
		if (IsCheckTime(1000))
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
		if (IsCheckTime(200))
		{
			//�ɸ�� ����� �����̷�
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle, 300, 14);
				lpMissile->angle = lpUnit->angle - 2 * PI / 8 * i;
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
				
			}
			//�ɸ�� ����� �������̷�
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
		
	//2??????
	else if (createLine == 1)
	{
		if (IsCheckTime(100))
		{
			//???��? ???
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
			//???��? ???
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
			//???��? ???
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
			//???��? ???
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
			//???��? ???
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
		
		//??? ??????
		if(IsCheckTime(200))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->pos, lpUnit->angle, 500, 14);
			lpMissile->angle = lpUnit->angle - 2 * PI / 5*4;
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REFLECT]);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
		//??? ??????
		else if (IsCheckTime(300))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->pos, lpUnit->angle, 500, 14);
			lpMissile->angle = lpUnit->angle - 2 * PI / 5 * 1;
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REFLECT]);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
	}

	//3??????
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
