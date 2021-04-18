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

void SSJFactory::Init()
{
	pattern1 = new BasicPattern();
	pattern2 = new SpiralPattern();
	pattern3 = new ReverseSpiralPattern();
	pattern4 = new SinePattern();
	pattern5 = new ReflectPattern();
	pattern6 = new DelayBasicPattern(); 
	createLine = 0;
	delayTime_0 = 0;
	delayTime_1 = 0;
	delayTime_2 = 0;
	phaseChanger = 0;

}

void SSJFactory::Release()
{
	if (pattern1) delete pattern1; pattern1 = nullptr;
	if (pattern2) delete pattern2; pattern2 = nullptr;
	if (pattern3) delete pattern3; pattern3 = nullptr;
	if (pattern4) delete pattern4; pattern4 = nullptr;
	if (pattern5) delete pattern5; pattern5 = nullptr;
	if (pattern6) delete pattern6; pattern6 = nullptr;
}

void SSJFactory::Fire(Unit* lpUnit)
{
	//각 페이즈 발사 주기 설정부
	delayTime_0 += 0.1f;
	if (delayTime_0 > 1.5f) delayTime_0 = 0;

	delayTime_1 += 0.1f;
	if (delayTime_1 >= 5.0f) delayTime_1 = 0;
		
	delayTime_2 += 1;
	if (delayTime_2 >= 15) delayTime_2 = 0;

	phaseChanger++;
	if (phaseChanger >= 100) createLine = 1;
	if (phaseChanger >= 200) createLine = 2;

	//1페이즈
	if (createLine == 0)
	{
		//36방향으로 원처럼 발사
		if (1.0f < delayTime_0 && delayTime_0 < 1.099999f)
		{
			for (int i = 0; i < 36; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle - 2 * PI / 36 * i;
				lpMissile->speed = 200;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(pattern2);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
			}
		}
		//꽃모양 만드는 스파이럴
		for (int i = 0; i < 8; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 8 * i;
			lpMissile->speed = 300;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern2);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//꽃모양 만드는 역스파이럴
		for (int i = 0; i < 8; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 8 * i;
			lpMissile->speed = 300;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern3);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
	
	//2페이즈
	else if (createLine == 1)
	{
		//가두는 그물S
		for (int i = 0; i < 6; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern4);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//가두는 그물
		for (int i = 0; i < 6; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos.x = lpUnit->pos.x + 300;
			lpMissile->pos.y = lpUnit->pos.y - 300;
			lpMissile->angle = lpUnit->angle - 2*PI/6*i;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern4);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//가두는 그물
		for (int i = 0; i < 6; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos.x = lpUnit->pos.x - 300;
			lpMissile->pos.y = lpUnit->pos.y - 300;
			lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern4);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//가두는 그물
		for (int i = 0; i < 6; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos.x = lpUnit->pos.x - 300;
			lpMissile->pos.y = lpUnit->pos.y + 300;
			lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern4);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//가두는 그물
		for (int i = 0; i < 6; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos.x = lpUnit->pos.x + 300;
			lpMissile->pos.y = lpUnit->pos.y + 300;
			lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern4);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//반사 레이저
		if(delayTime_1 < 1.0f)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 5*4;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_03");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern5);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//반사 레이저
		else if (delayTime_1 < 2.0f)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 5*3;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_03");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern5);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//반사 레이저
		else if (delayTime_1 < 3.0f)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 5 * 1;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_03");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern5);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		//반사 레이저
		else if (delayTime_1 < 4.0f)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 5 * 2;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_03");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(pattern5);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}

	//3페이즈
	else if (createLine == 2)
	{
		if (delayTime_2 == 1)
		{
			for (int j = 0; j < 10; ++j)
			{
				for (int i = 0; i < 20; ++i)
				{
					if (patternArray[i + j * 20] == 1)
					{
						Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
						lpMissile->pos = lpUnit->pos;
						lpMissile->angle = lpUnit->angle - PI*4/5 - 0.05 * i;
						lpMissile->speed = 200;
						lpMissile->elapsedTime = 0;
						lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
						lpMissile->deltaMove.deltaPos = { 0,  0 };
						lpMissile->SetPattern(pattern6);
						lpMissile->SetDelayTime(0.07f * j);
						MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
					}
					else
						continue;

				}

			}
		}

	}
}
