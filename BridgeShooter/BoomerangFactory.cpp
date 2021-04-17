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
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->pos = lpUnit->pos;
		lpMissile->angle = lpUnit->angle;
		lpMissile->speed = 200;
		lpMissile->elapsedTime = 0;
		lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
		lpMissile->SetPattern(lpPattern);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
	
}
