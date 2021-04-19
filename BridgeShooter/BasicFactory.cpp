#include "BasicFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "SinePattern.h"
#include "BoomerangPattern.h"
#include "SpiralPattern.h"
#include "ReflectPattern.h"

void BasicFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::BFCP_NONE);
	vLpPatterns[CREATE_PATTERN::BFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::BFCP_REFLECT] = new ReflectPattern();

	maxCreateLIne = 3;
}

void BasicFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void BasicFactory::Fire(Unit* lpUnit)
{
	if (createLine == 0)
	{
		// ±‚∫ª≈∫
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle, 200, 20);
		lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_BASIC]);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
	else if (createLine == 1)
	{
		// ªÍ≈∫
		for (int i = 0; i < 20; ++i)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_01", lpUnit->pos, lpUnit->angle + ((float)(rand() % 101) - 50) / 100, rand() % 100 + 100, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_BASIC]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}
	else if (createLine == 2)
	{
		// π›ªÁ
		for (int i = -3; i < 4; i += 2)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_02", lpUnit->pos, lpUnit->angle + PI / 24 * i, 400, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_REFLECT]);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
	}

	//for (int i = 0; i < 8; ++i)
	//{
	//	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	//	lpMissile->pos = lpUnit->pos;
	//	lpMissile->angle = lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i;
	//	//lpMissile->angle = -PI * 4 / 5;
	//	lpMissile->speed = 100;
	//	lpMissile->elapsedTime = 0;
	//	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	//	lpMissile->deltaMove.deltaPos = { 0,  0 };
	//	lpMissile->SetPattern(pattern);
	//	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	//}

	//for (int i = -3; i < 4; ++i)
	//{
	//	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	//	lpMissile->pos = lpUnit->pos;
	//	lpMissile->angle = lpUnit->angle + PI / 16 * i;
	//	lpMissile->speed = 300;
	//	lpMissile->elapsedTime = 0;
	//	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
	//	lpMissile->deltaMove.deltaPos = { 0,  0 };
	//	lpMissile->SetPattern(pattern2);
	//	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	//}
}
