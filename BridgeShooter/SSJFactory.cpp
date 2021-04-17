#include "SSJFactory.h"
#include "Factory.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "Missile.h"
#include "SinePattern.h"
#include "SpiralPattern.h"
#include "ReverseSpiralPattern.h"
#include "SinePattern.h"

void SSJFactory::Init()
{
	pattern1 = new BasicPattern();
	pattern2 = new SpiralPattern();
	pattern3 = new ReverseSpiralPattern();
	pattern4 = new SinePattern();
	createLine = 1;
}

void SSJFactory::Release()
{
	if (pattern1) delete pattern1; pattern1 = nullptr;
	if (pattern2) delete pattern2; pattern2 = nullptr;
	if (pattern3) delete pattern3; pattern3 = nullptr;
	if (pattern4) delete pattern4; pattern4 = nullptr;
}

void SSJFactory::Fire(Unit* lpUnit)
{
	//5개씩 3방향으로 주기적으로 발사
	//if ((int)(lpUnit->elapsedTime*10) %3 == 0)
	//{
	//	for (int i = -2; i < 3; ++i)
	//	{
	//		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	//		lpMissile->pos = lpUnit->pos;
	//		lpMissile->angle = lpUnit->angle - 0.05f * i -PI;
	//		lpMissile->speed = 200;
	//		lpMissile->elapsedTime = 0;
	//		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	//		lpMissile->deltaMove.deltaPos = { 0,  0 };
	//		lpMissile->SetPattern(pattern1);
	//		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	//	}
	//}	
	//else if ((int)(lpUnit->elapsedTime*10) %3 == 1)
	//{
	//	for (int i = -2; i < 3; ++i)
	//	{
	//		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	//		lpMissile->pos = lpUnit->pos;
	//		lpMissile->angle = lpUnit->angle - 0.05f * i - PI - 0.8f;
	//		lpMissile->speed = 200;
	//		lpMissile->elapsedTime = 0;
	//		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	//		lpMissile->deltaMove.deltaPos = { 0,  0 };
	//		lpMissile->SetPattern(pattern1);
	//		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	//	}
	//}
	//else if ((int)(lpUnit->elapsedTime * 10) % 3 == 2)
	//{
	//	for (int i = -2; i < 3; ++i)
	//	{
	//		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	//		lpMissile->pos = lpUnit->pos;
	//		lpMissile->angle = lpUnit->angle - 0.05f * i - PI +0.8f;
	//		lpMissile->speed = 200;
	//		lpMissile->elapsedTime = 0;
	//		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	//		lpMissile->deltaMove.deltaPos = { 0,  0 };
	//		lpMissile->SetPattern(pattern1);
	//		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	//	}
	//}
		
	if (createLine == 0)
	{
		//36방향으로 원처럼 발사
		if ((int)(lpUnit->elapsedTime * 10) % 5 == 0)
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
	
	else if (createLine == 1)
	{
	/*	for (int i = 0; i < 6; ++i)
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
		}*/
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
	}
}
