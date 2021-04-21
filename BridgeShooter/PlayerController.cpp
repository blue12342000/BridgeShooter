#include "PlayerController.h"
#include "Unit.h"

void PlayerController::Init()
{
	mKeyMap.insert(make_pair(INPUT_COMMAND::LEFT, UnitEvent{ INPUT_TYPE::STAY, 'A' }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::RIGHT, UnitEvent{ INPUT_TYPE::STAY, 'D' }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::UP, UnitEvent{ INPUT_TYPE::STAY, 'W' }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::DOWN, UnitEvent{ INPUT_TYPE::STAY, 'S' }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::ATTACK, UnitEvent{ INPUT_TYPE::STAY, VK_SPACE }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::DOWNGRADE, UnitEvent{ INPUT_TYPE::ONCE, VK_OEM_4 }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::UPGRADE, UnitEvent{ INPUT_TYPE::ONCE, VK_OEM_6 }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::INERTIA, UnitEvent{ INPUT_TYPE::ONCE, VK_OEM_7 }));
	origin = { WINSIZE_WIDTH / 2.0f, WINSIZE_HEIGHT * 9 / 10.0f };
}

void PlayerController::Release()
{
}

void PlayerController::Update(float deltaTime)
{
	if (lpUnit)
	{
		if (!lpUnit->IsReady())
		{
			float distance = pow(origin.y - lpUnit->pos.y, 2) + pow(origin.x - lpUnit->pos.x, 2);
			if (distance > 100)
			{
				lpUnit->Translate(POINTFLOAT{ origin.x - lpUnit->pos.x, origin.y - lpUnit->pos.y });
			}
			if (distance < 100)
			{
				lpUnit->SetIsReady(true);
				lpUnit->SetInetia(false);
			}
		}
		else
		{
			for (auto& pair : mKeyMap)
			{
				switch (pair.second.type)
				{
				case INPUT_TYPE::ONCE:
					if (KeyManager::GetSingleton()->IsKeyDownOne(pair.second.key))
					{
						pair.second.lpCmd();
					}
					break;
				case INPUT_TYPE::STAY:
					if (KeyManager::GetSingleton()->IsKeyDownStay(pair.second.key))
					{
						pair.second.lpCmd();
					}
					break;
				}
			}
		}
		lpUnit->Update(deltaTime);
	}
}

void PlayerController::Render(HDC hdc)
{
	if (lpUnit) lpUnit->Render(hdc);
}

void PlayerController::SetUnit(Unit* lpUnit)
{
	this->lpUnit = lpUnit;
	this->lpUnit->pos = { (float)WINSIZE_WIDTH / 2, (float)WINSIZE_HEIGHT + 300 };
	this->lpUnit->angle = PI * 3 / 2;
	this->lpUnit->SetInetia(true);
	this->lpUnit->SetIsReady(false);
	mKeyMap[INPUT_COMMAND::LEFT].lpCmd = bind(&Unit::Translate, lpUnit, POINTFLOAT{ -10, 0 });
	mKeyMap[INPUT_COMMAND::RIGHT].lpCmd = bind(&Unit::Translate, lpUnit, POINTFLOAT{ 10, 0 });
	mKeyMap[INPUT_COMMAND::UP].lpCmd = bind(&Unit::Translate, lpUnit, POINTFLOAT{ 0, -10 });
	mKeyMap[INPUT_COMMAND::DOWN].lpCmd = bind(&Unit::Translate, lpUnit, POINTFLOAT{ 0, 10 });
	mKeyMap[INPUT_COMMAND::ATTACK].lpCmd = bind(&Unit::Fire, lpUnit);

	mKeyMap[INPUT_COMMAND::DOWNGRADE].lpCmd = bind(&Unit::ChangeFactoryLine, lpUnit, -1);
	mKeyMap[INPUT_COMMAND::UPGRADE].lpCmd = bind(&Unit::ChangeFactoryLine, lpUnit, 1);
	mKeyMap[INPUT_COMMAND::INERTIA].lpCmd = bind(&Unit::ToggleInertia, lpUnit);
}
