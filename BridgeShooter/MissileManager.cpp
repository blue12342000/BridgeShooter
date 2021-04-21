#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init()
{
	vector<Missile*> vMissiles;
	vMissiles.reserve(5000);
	vLpDeactive.reserve(5000);
	mvLpMissiles.insert(make_pair(UNIT_KIND::PLAYER, vMissiles));
	mvLpMissiles.insert(make_pair(UNIT_KIND::ENEMY, vMissiles));
	mvLpMissiles.insert(make_pair(UNIT_KIND::BOSS, vMissiles));
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
			if (vLpMissile[i]->pos.x < WINSIZE_LEFT || vLpMissile[i]->pos.y < WINSIZE_TOP
				|| vLpMissile[i]->pos.x > WINSIZE_RIGHT || vLpMissile[i]->pos.y > WINSIZE_BOTTOM)
			{
				vLpDeactive.push_back(vLpMissile[i]);
				vLpMissile.erase(vLpMissile.begin() + i);
			}
			else
			{
				vLpMissile[i]->Update(deltaTime);
				++i;
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
	Missile* lpMissile;
	if (vLpDeactive.empty())
	{
		lpMissile = new Missile();
		lpMissile->Init();
		return lpMissile;
	}
	else
	{
		Missile* lpMissile = vLpDeactive.back();
		vLpDeactive.pop_back();
		return lpMissile;
	}
}

void MissileManager::ClearActiveMissile()
{
	for (auto& pair : mvLpMissiles)
	{
		// 이부분은 InGameScene에 있어야한다.
		// 남은탄 all 삭제전에 남은 탄들위치에 Item 을 추가적으로 생성해 줘야 한다.
		vector<Missile*> vLpMissile = pair.second;
		for (int i = 0; i < vLpMissile.size(); ++i)
		{
			EffectManager::GetSingleton()->PlayImage(vLpMissile[i]->pos, "EFFECT_01", 10);
		}

		vLpDeactive.insert(vLpDeactive.end(), pair.second.begin(), pair.second.end());
		pair.second.clear();
	}
}
