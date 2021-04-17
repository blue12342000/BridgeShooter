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
	pattern = new ReflectPattern();
	pattern2 = new BasicPattern();
}

void BasicFactory::Fire(Unit* lpUnit)
{
	for (int i = 0; i < 8; ++i)
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = lpUnit->pos;
		lpMissile->angle = lpUnit->angle + lpUnit->elapsedTime * 1.5f + PI / 4 * i;
		//lpMissile->angle = -PI * 4 / 5;
		lpMissile->speed = 100;
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->deltaMove.deltaPos = { 0,  0 };
		lpMissile->SetPattern(pattern);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}

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
