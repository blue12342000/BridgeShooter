#include "SSJFactory.h"
#include "Factory.h"
#include "Unit.h"
#include "BasicPattern.h"
#include "Missile.h"
#include "SinePattern.h"
#include "SpiralPattern.h"
#include "SinePattern.h"
#include "ReflectPattern.h"
#include "BridgeShooter.h"


void SSJFactory::Init()
{
	vLpPatterns.resize(CREATE_PATTERN::SFCP_NONE);
	vLpPatterns[CREATE_PATTERN::SFCP_BASIC] = new BasicPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_SPIRAL] = new SpiralPattern();
	vLpPatterns[CREATE_PATTERN::SFCP_SINE] = new SinePattern();
	vLpPatterns[CREATE_PATTERN::SFCP_REFLECT] = new ReflectPattern();

	createLine = 0;
	maxCreateLIne = 4;

	phaseChanger = 0;

	lastEndingLine = 0;
	SetCheckTime(10);
	SetCheckTime(100);
	SetCheckTime(200);
	SetCheckTime(300);
	SetCheckTime(1000);
	SetCheckTime(3000);
}

void SSJFactory::Release()
{
	for (auto& lpPattern : vLpPatterns)
	{
		delete lpPattern;
	}
	vLpPatterns.clear();
}

void SSJFactory::Fire(Unit* lpUnit)
{
	if (createLine < 3)
	{
		phaseChanger++;
		if (phaseChanger >= 5000) createLine = 1;
		if (phaseChanger >= 10000) createLine = 2;
	}

	//1 phase
	if (createLine == 0)
	{

		if (IsCheckTime(1000))
		{
			for (int i = 0; i < 36; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_07", lpUnit->angle - 2 * PI / 36 * i, Transform{ lpUnit->pos, lpUnit->angle - 2 * PI / 36 * i, 200 }, 14);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}

		}
		if (IsCheckTime(200))
		{

			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_08", lpUnit->angle + PI / 4 * i, Transform{ lpUnit->pos, lpUnit->angle + PI / 4 * i, PI / 4, 0, 500 }, 14, 0);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);

			}
			for (int i = 0; i < 8; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_08", lpUnit->angle + PI / 4 * i, Transform{ lpUnit->pos, lpUnit->angle + PI / 4 * i, -PI / 4, 0, 500 }, 14, 0);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SPIRAL]);
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}

	}

	//2 phase
	else if (createLine == 1)
	{
		if (IsCheckTime(100))
		{
			//???¥ä? ???
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->angle - 2 * PI / 6 * i, Transform{ lpUnit->pos, PI / 2, 500, PI, 100 }, 14, 0);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
			//???¥ä? ???
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->angle - 2 * PI / 6 * i, Transform{ { lpUnit->pos.x - 300, lpUnit->pos.y + 300 }, PI / 2, 500, PI, 100 }, 14, 0);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
			//???¥ä? ???
			for (int i = 0; i < 6; ++i)
			{
				Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
				lpMissile->SetMissile("MISSILE_02", lpUnit->angle - 2 * PI / 6 * i, Transform{ { lpUnit->pos.x + 300, lpUnit->pos.y + 300 }, PI / 2, 500, PI, 100 }, 14, 0);
				lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_SINE]);
				lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
				MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
			}
		}

		//??? ??????
		if (IsCheckTime(200))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->angle + PI / 5, Transform{ lpUnit->pos, lpUnit->angle + PI / 5, 500 }, 14);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REFLECT]);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
		}
		if (IsCheckTime(300))
		{
			Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
			lpMissile->SetMissile("MISSILE_03", lpUnit->angle + PI / 5 * 4, Transform{ lpUnit->pos, lpUnit->angle + PI / 5 * 4, 500 }, 14);
			lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_REFLECT]);
			lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
			MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
		}

	}

	//3 phase
	else if (createLine == 2)
	{
		if (IsCheckTime(3000))
		{
			if (lpUnit->angle == 0)
			{
				for (int j = 0; j < 10; ++j)
				{
					for (int i = 0; i < 20; ++i)
					{
						if (patternArray[i + j * 20] == 0)
						{
							Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
							lpMissile->SetMissile("MISSILE_01", lpUnit->angle - PI * 4 / 5 - 0.05 * i - PI / 2, Transform{ lpUnit->pos, lpUnit->angle - PI * 4 / 5 - 0.05f * i - PI / 2, 200.0f }, 14, 0.07f * j);
							lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
							lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
							MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
						}
						else
							continue;

					}

				}
			}
			else
			{
				for (int j = 0; j < 10; ++j)
				{
					for (int i = 0; i < 20; ++i)
					{
						if (patternArray[i + j * 20] == 0)
						{
							Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile();
							lpMissile->SetMissile("MISSILE_01", lpUnit->angle - PI * 4 / 5 - 0.05 * i + PI / 2, Transform{ lpUnit->pos, lpUnit->angle - PI * 4 / 5 - 0.05f * i + PI / 2, 200.0f }, 14, 0.07f * j);
							lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
							lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
							MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
						}
						else
							continue;

					}

				}
			}

		}

	}

	//credit
	else if (createLine == 3)
	{
		if (IsCheckTime(100))
		{
			for (int i = 0; i < 30; ++i)
			{
				if (endingCredit[lastEndingLine][i] == 0)
				{
					Missile* lpMissile = MissileManager::GetSingleton()->CreateMissile(); // -PI * 3 / 4 + (PI / 2 / 43.0f) * i
					lpMissile->SetMissile("MISSILE_01", -PI / 2, Transform{ { WINSIZE_WIDTH / 30.0f * i, WINSIZE_HEIGHT},0, 200.0f }, 14);
					lpMissile->SetPattern(vLpPatterns[CREATE_PATTERN::SFCP_BASIC]);
					lpMissile->collider.type = COLLIDER_TYPE::CIRCLE;
					MissileManager::GetSingleton()->AddMissile(lpUnit->GetUnitKind(), lpMissile);
				}
			}
			lastEndingLine = (lastEndingLine + 1) % 44;
		}
	}
}
