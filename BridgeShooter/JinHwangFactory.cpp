#include "JinHwangFactory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "ReflectPattern.h"
#include "SpiralPattern.h"
#include "ReverseSpiralPattern.h"
#include "BoomerangPattern.h"
#include "Missile.h"
#include "Unit.h"

void JinHwangFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::JFCP_NONE);
	vLpPatterns[CREATE_PATTERN::JFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_SPIRAL] = new SpiralPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_REVERSE_SPIRAL] = new ReverseSpiralPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_BOOMERANG] = new BoomerangPattern();

	createLine = 1;
	maxCreateLIne = 3;
}

void JinHwangFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void JinHwangFactory::Fire(Unit* lpUnit)
{
	if (createLine == 0)
	{
		if ((((int)lpUnit->elapsedTime) % 20) < 10)
		{
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i;
				lpMissile->speed = 300;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		else
		{
			for (int i = 0; i < 16; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 8 * i;
				lpMissile->speed = 200;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->delayTime = (float)i * 0.1f;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
	else if (createLine == 1)
	{
		if ((((int)lpUnit->elapsedTime) % 20) < 10)
		{
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i;
				lpMissile->speed = 100;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i;
				lpMissile->speed = 100;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_REVERSE_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}

		if ((((int)lpUnit->elapsedTime) % 20) == 0)
		{
			for (int i = -1; i < 2; i += 2)
			{
				for (int l = 0; l < 6; ++l)
				{
					Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
					lpMissile->pos = lpUnit->pos;
					lpMissile->angle = lpUnit->angle + PI * 2 / 5 * i;
					lpMissile->speed = 400;
					lpMissile->elapsedTime = 0;
					lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_02");
					lpMissile->deltaMove.deltaPos = { 0,  0 };
					lpMissile->delayTime = 0.02f * l;
					lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_REFLECT]);
					MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
				}
			}
		}
	}
	else if (createLine == 2)
	{
		if ((((int)lpUnit->elapsedTime) % 20) < 10)
		{
			for (int i = 0; i < 16; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->pos = lpUnit->pos;
				lpMissile->angle = lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i;
				lpMissile->speed = 300;
				lpMissile->elapsedTime = 0;
				lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
				lpMissile->deltaMove.deltaPos = { 0,  0 };
				lpMissile->delayTime = -10;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::JFCP_BOOMERANG]);
				MissileManager::GetSingleton()->AddMissile(UNIT_KIND::ENEMY, lpMissile);
			}
		}
	}
}
