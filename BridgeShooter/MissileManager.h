#pragma once
#include "Singleton.h"
#include "BridgeShooter.h"

class Missile;
class MissileManager : public Singleton<MissileManager>
{
private:
	map<UNIT_KIND, vector<Missile*>> mvLpMissiles;
	vector<Missile*> vLpDeactive;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);

	Missile* CreateMissile();
	void ClearActiveMissile();
	
	inline vector<Missile*>& GetLpMissiles(UNIT_KIND kind) { return mvLpMissiles[kind]; }
	inline void AddMissile(UNIT_KIND userKind, Missile* lpMissile) { mvLpMissiles[userKind].push_back(lpMissile); }
	inline vector<Missile*>::iterator DisableMissile(UNIT_KIND kind, int index) { vLpDeactive.push_back(*(mvLpMissiles[kind].begin() + index)); return mvLpMissiles[kind].erase(mvLpMissiles[kind].begin() + index); }
};

