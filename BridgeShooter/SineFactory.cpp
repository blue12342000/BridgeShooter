#include "BridgeShooter.h"
#include "SineFactory.h"
#include "SinePattern.h"
#include "Missile.h"

SineFactory::SineFactory()
{
	pattern = new SinePattern();
}

SineFactory::~SineFactory()
{
	if (pattern) delete pattern;
}

void SineFactory::Fire(GameObject* lpObject)
{
	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	lpMissile->pos = lpObject->pos;
	lpMissile->angle = lpObject->angle;
	lpMissile->speed = 300;
	lpMissile->elapsedTime = 0;
	lpMissile->lpImage = ImageManager::GetSingleton()->FindImage("MISSILE_01");
	lpMissile->lpPattern = pattern;
	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
}
