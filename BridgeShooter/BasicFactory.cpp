#include "BasicFactory.h"
#include "BridgeShooter.h"
#include "Missile.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "ReflectPattern.h"
#include "GuideBasicPattern.h"

void BasicFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::BFCP_NONE);
	vLpPatterns[CREATE_PATTERN::BFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::BFCP_REFLECT] = new ReflectPattern();
	vLpPatterns[CREATE_PATTERN::BFCP_GUIDE_BASIC] = new GuideBasicPattern();

	maxCreateLIne = 5;
	SetCheckTime(2000);
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
	if (IsCheckTime(2000))
	{
		if (createLine == 1)
		{
			// ±‚∫ª≈∫
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_01", PI/2, Transform{ lpUnit->pos, 0, 200 }, 20);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_BASIC]);
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
		}
		else if (createLine == 2)
		{
			// ªÍ≈∫
			for (int i = 0; i < 20; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_01", PI / 2 + ((float)(rand() % 101) - 50) / 100, Transform{ lpUnit->pos, 0, rand() % 100 + 100.0f }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
		else if (createLine == 3)
		{
			// π›ªÁ
			for (int i = -3; i < 4; i += 2)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_07", PI / 2 + PI / 24 * i, Transform{ lpUnit->pos, PI / 2 + PI / 24 * i, 400 }, 20);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_REFLECT]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}
		else if (createLine == 4)
		{
			// ≈∏∞Ÿ∞¯∞›
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_02", PI / 2, Transform{ lpUnit->pos, PI / 2, 250 }, 20, 0.01f);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::BFCP_GUIDE_BASIC]);
			lpMissile->SetLpTarget(&lpUnit->GetTarget());
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
		}
	}
	
}
