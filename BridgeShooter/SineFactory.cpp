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
		lpMissile->SetMissile("MISSILE_01", lpObject->angle, Transform{ lpObject->pos, PI / 2 * i, 500, PI * 8, 30 }, 20);
		lpMissile->SetPattern(pattern);
		MissileManager::GetSingleton()->AddMissile(UNIT_KIND::PLAYER, lpMissile);
	}
}
