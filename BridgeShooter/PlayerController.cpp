#include "PlayerController.h"
#include "Unit.h"

void PlayerController::Init()
{
	mKeyMap.insert(make_pair(INPUT_COMMAND::LEFT, UnitEvent{ INPUT_TYPE::STAY, 'A' }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::RIGHT, UnitEvent{ INPUT_TYPE::STAY, 'D' }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::UP, UnitEvent{ INPUT_TYPE::STAY, 'W' }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::DOWN, UnitEvent{ INPUT_TYPE::STAY, 'S' }));
	mKeyMap.insert(make_pair(INPUT_COMMAND::ATTACK, UnitEvent{ INPUT_TYPE::STAY, VK_SPACE }));
}

void PlayerController::Release()
{
}

void PlayerController::Update(float deltaTime)
{
	if (lpUnit)
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

		lpUnit->Update(deltaTime);
	}
}

void PlayerController::Render(HDC hdc)
{
	if (lpUnit) lpUnit->Render(hdc);
}

void PlayerController::SetController(Unit* lpUnit)
{
	this->lpUnit = lpUnit;
	mKeyMap[INPUT_COMMAND::LEFT].lpCmd = bind(&Unit::Translate, lpUnit, POINT{ -1, 0 });
	mKeyMap[INPUT_COMMAND::RIGHT].lpCmd = bind(&Unit::Translate, lpUnit, POINT{ 1, 0 });
	mKeyMap[INPUT_COMMAND::UP].lpCmd = bind(&Unit::Translate, lpUnit, POINT{ 0, -1 });
	mKeyMap[INPUT_COMMAND::DOWN].lpCmd = bind(&Unit::Translate, lpUnit, POINT{ 0, 1 });
	mKeyMap[INPUT_COMMAND::ATTACK].lpCmd = bind(&Unit::Fire, lpUnit);
}
