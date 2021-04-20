#include "BridgeShooter.h"
#include "SineFactory.h"
#include "SinePattern.h"
#include "Missile.h"
#include "Unit.h"

void SineFactory::Init()
{
	pattern = new SinePattern();
}

void SineFactory::Fire(Unit* lpObject)
{
	Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
	lpMissile->SetMissile("MISSILE_01", lpObject->pos, lpObject->angle, 300, 20);
	lpMissile->SetPattern(pattern);
	MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
}
