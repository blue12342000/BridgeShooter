#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init()
{
	vector<Missile*> vMissiles;
	vMissiles.reserve(10000);
	mvLpMissiles.insert(make_pair(UNIT_KIND::PLAYER, vMissiles));
	mvLpMissiles.insert(make_pair(UNIT_KIND::ENEMY, vMissiles));
	return S_OK;
}

void MissileManager::Release()
{
	for (auto& pair : mvLpMissiles)
	{
		for (auto& lpMissile : pair.second)
		{
			lpMissile->Release();
			delete lpMissile;
		}
		pair.second.clear();
	}
}

void MissileManager::Update(float deltaTime)
{
	for (auto& pair : mvLpMissiles)
	{
		for (auto& lpMissile : pair.second)
		{
			lpMissile->Update(deltaTime);
		}
	}
}

void MissileManager::Render(HDC hdc)
{
	for (auto& pair : mvLpMissiles)
	{
		for (auto& lpMissile : pair.second)
		{
			lpMissile->Render(hdc);
		}
	}
}
