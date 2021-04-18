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
	lpPattern1 = new BasicPattern();
	lpPattern2 = new SpiralPattern();
	lpPattern3 = new ReverseSpiralPattern();
	lpPattern4 = new SinePattern();
	lpPattern5 = new ReflectPattern();
	lpPattern6 = new DelayBasicPattern(); 
	createLine = 0;
	delayTime_0 = 0;

	phaseChanger = 0;

}

void SSJFactory::Release()
{
	if (lpPattern1) delete lpPattern1; lpPattern1 = nullptr;
	if (lpPattern2) delete lpPattern2; lpPattern2 = nullptr;
	if (lpPattern3) delete lpPattern3; lpPattern3 = nullptr;
	if (lpPattern4) delete lpPattern4; lpPattern4 = nullptr;
	if (lpPattern5) delete lpPattern5; lpPattern5 = nullptr;
	if (lpPattern6) delete lpPattern6; lpPattern6 = nullptr;
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
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle - 2 * PI / 36 * i;
				lpMissile->speed = 200;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(lpPattern1);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.width = 14;
				lpMissile->collider.height = 14;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}

		}
		if (delayTime_0 % 30 == 0)
		{
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
				lpMissile->SetPattern(lpPattern2);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.width = 14;
				lpMissile->collider.height = 14;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
				
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
				lpMissile->SetPattern(lpPattern3);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.width = 14;
				lpMissile->collider.height = 14;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
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
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
				lpMissile->speed = 500;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(lpPattern4);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.width = 14;
				lpMissile->collider.height = 14;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
			//가두는 그물
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos.x = lpUnit->pos.x + 300;
				lpMissile->pos.y = lpUnit->pos.y - 300;
				lpMissile->angle = lpUnit->angle - 2 * PI / 6 * i;
				lpMissile->speed = 500;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(lpPattern4);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.width = 14;
				lpMissile->collider.height = 14;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
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
				lpMissile->SetPattern(lpPattern4);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.width = 14;
				lpMissile->collider.height = 14;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
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
				lpMissile->SetPattern(lpPattern4);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.width = 14;
				lpMissile->collider.height = 14;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
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
				lpMissile->SetPattern(lpPattern4);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->collider.width = 14;
				lpMissile->collider.height = 14;
				lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		
		//반사 레이저
		if(delayTime_0 % 51 == 0)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 5*4;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_03");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(lpPattern5);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			lpMissile->collider.width = 14;
			lpMissile->collider.height = 14;
			lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
		//반사 레이저
		else if (delayTime_0 % 71 == 0)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - 2 * PI / 5 * 1;
			lpMissile->speed = 500;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_03");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(lpPattern5);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			lpMissile->collider.width = 14;
			lpMissile->collider.height = 14;
			lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
		}
	}

	//3페이즈
	else if (createLine == 2)
	{
		if (delayTime_0 % 500 == 0)
		{
			for (int j = 0; j < 10; ++j)
			{
				for (int i = 0; i < 20; ++i)
				{
					if (patternArray[i + j * 20] == 1)
					{
						Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
						lpMissile->pos = lpUnit->pos;
						lpMissile->angle = lpUnit->angle - PI*4/5 - 0.06 * i;
						lpMissile->speed = 100;
						lpMissile->elapsedTime = 0;
						lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
						lpMissile->deltaMove.deltaPos = { 0,  0 };
						lpMissile->SetPattern(lpPattern6);
						lpMissile->SetDelayTime(0.1f * j);
						lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
						lpMissile->collider.width = 14;
						lpMissile->collider.height = 14;
						lpMissile->collider.SetHitBox(lpMissile->pos, lpMissile->deltaMove.deltaPos, 14, 14);
						MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
					}
					else
						continue;

				}

			}
		}

	}
}
