#include "Planet04Factory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "RainPattern.h"
#include "ReflectPattern.h"
#include "SpiralPattern.h"
#include "Missile.h"
#include "Unit.h"

void Planet04Factory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::PLANET04_NONE);
	vLpPatterns[CREATE_PATTERN::PLANET04_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_RAIN] = new RainPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::PLANET04_SPRIAL] = new SpiralPattern();

	isPattern01 = true;
	isPattern02 = false;
	isPattern03 = false;

	maxCreateLIne = 0;
	count = 0;
}

void Planet04Factory::Release()
{
	//자동으로 타입 적게해줌 auto. 싱기방기
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void Planet04Factory::Fire(Unit* lpUnit)
{
	++bossCount;	//200 되면 다음 페이즈 전환 테스트용
	//1페이즈
	if (isPattern01 && bossCount < 3000)
	{
		if ((int)(lpUnit->elapsedTime * 10) % 12 == 0)	//타이머
		{
			for (int i = -1; i < 2; ++i)	//한번에 여러개 나가게 하기
			{
				++count;
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle - (PI / 16 * i) +count;
				lpMissile->speed = 150;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
				//if (count >= 200) count *= -1;
			}
		}
	}

	//2페이즈
	if (isPattern02 && bossCount < 3000)
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
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		if (count >= 9) count *= -1;

		if ((int)(lpUnit->elapsedTime * 10) % 6 == 0)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = lpUnit->angle - PI / 32;
			lpMissile->speed = 200;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
			lpMissile->deltaMove.deltaPos = { 0,  0 };
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::PLANET04_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}

	//3페이즈
	if (isPattern03 && bossCount < 3000)
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
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		if (count >= 9) count *= -1;


		if ((int)(lpUnit->elapsedTime * 10) % 3 == 0)
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
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
			}
		}
	}

	if (isPattern01 && bossCount >= 3000)
	{
		bossCount = 0;
		isPattern01 = false;
		isPattern02 = true;
	}
	else if (isPattern01 == false && isPattern02 && bossCount >= 3000)
	{
		bossCount = 0;
		isPattern02 = false;
		isPattern03 = true;
	}
	else if (isPattern03 && bossCount >= 3000)
	{
		bossCount = 0;
		isPattern03 = false;
	}
}