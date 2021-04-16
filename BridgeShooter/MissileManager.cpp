#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init()
{
	vector<Missile*> vMissiles;
	vMissiles.reserve(5000);
	vLpDeactive.reserve(5000);
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
		vector<Missile*>& vLpMissile = pair.second;
		for (int i = 0; i < vLpMissile.size();)
		{
			if (vLpMissile[i]->pos.x < -200 || vLpMissile[i]->pos.y < -200
				|| vLpMissile[i]->pos.x > WINSIZE_WIDTH + 200 || vLpMissile[i]->pos.y > WINSIZE_HEIGHT + 200)
			{
				vLpDeactive.push_back(vLpMissile[i]);
				vLpMissile.erase(vLpMissile.begin() + i);
			}
			else
			{
				vLpMissile[i++]->Update(deltaTime);
			}
		}
	}
}
  
void MissileManager::Render(HDC hdc)
{
	for (auto pair : mvLpMissiles)
	{
		vector<Missile*> vLpMissile = pair.second;
		for (int i = 0; i < vLpMissile.size();++i)
		{
			vLpMissile[i]->Render(hdc);
		}
	}
}

Missile* MissileManager::CreateMissile()
{
	if (vLpDeactive.empty()) return new Missile();
	else
	{
		Missile* lpMissile = vLpDeactive.back();
		vLpDeactive.pop_back();
		return lpMissile;
	}
}
