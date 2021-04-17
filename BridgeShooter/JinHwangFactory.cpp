#include "JinHwangFactory.h"
#include "BridgeShooter.h"
#include "BasicPattern.h"
#include "ReflectPattern.h"
#include "SpiralPattern.h"
#include "Missile.h"
#include "Unit.h"

void JinHwangFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::JFCP_NONE);
	vLpPatterns[CREATE_PATTERN::JFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::JFCP_SPIRAL] = new SpiralPattern();

	maxCreateLIne = 0;
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
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}
