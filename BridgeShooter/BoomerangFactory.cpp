#include "BoomerangFactory.h"
#include "Pattern.h"
#include"BoomerangPattern.h"
#include"Missile.h"
#include "Unit.h"
void BoomerangFactory::Init()
{
	lpPattern = new BoomerangPattern();
}

void BoomerangFactory::Release()
{
	if (lpPattern) {
		delete lpPattern;
		lpPattern = nullptr;
	}
}

void BoomerangFactory::Fire(Unit* lpUnit)
{
	if (lpUnit) {
		for (int i = 0; i < missileNum; i++)
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetDelayTime(-10);//-·Î
			lpMissile->pos = lpUnit->pos;
			lpMissile->angle = 2*PI*i/ missileNum;
			lpMissile->speed = 170;
			lpMissile->elapsedTime = 0;
			lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
			lpMissile->SetPattern(lpPattern);
			MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
		}
		
	}
	
}
