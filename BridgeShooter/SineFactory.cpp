#include "BridgeShooter.h"
#include "SineFactory.h"
#include "SinePattern.h"
#include "Missile.h"
#include "Unit.h"
#include "SpiralPattern.h"

void SineFactory::Init()
{
	pattern = new SinePattern();
}

void SineFactory::Fire(Unit* lpObject)
{
	for (int i = -1; i < 2; i += 2)
	{
		Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
		lpMissile->SetSineMissile("MISSILE_01", lpObject->pos, lpObject->angle, PI / 2 * i, PI * 8, 30, 500, 20, 0);
		lpMissile->SetPattern(pattern);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}
